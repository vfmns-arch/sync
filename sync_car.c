#include "sync_car.c"

#include <stdlib.h>

void station_init(struct station *station){
  pthread_mutex_init(&station->mutex, NULL);
  pthread_cond_init(&station->cond, NULL);

  station->waiting_passengers = 0;
  station->available_seats = 0;
  station->passengers_to_board = 0;
  station->passengers_boarded = 0;
  station->car_present = 0;
}

void station_load_car(struct station *station, int count){
  pthread_mutex_lock(&station_mutex);
  station->car_present = 1;
  station->available_seats = count;
  station->passengers_boarded = 0;
  int passengers = station->waiting_passengers;
  if (passengers > count) {
    passengers = count;
  }
  station->passengers_to_board = passengers;
  if (passengers == 0) {
    station->car_present = 0;
    station->available_seats = 0;
    pthread_cond_broadcast(&station->cond);
    pthread_mutex_unlock(&station->mutex);
    return;
  }
  pthread_cond_broadcast(&station->cond);
  while (station->passengers_boarded < passengers) {
    pthread_cond_wait(&station->cond, &station->mutex);
  }
  station->car_present = 0;
  station->available_seats = 0;
  station->passengers_to_board = 0;
  pthread_cond_broadcast(&station->cond);
  pthread_mutex_unlock(&station->mutex);
}

void station_wait_for_car(struct station *station) {
  pthread_mutex_lock(&station->mutex);
  station->waiting_passengers++;
  while (!station->car_present || station->available_seats <= 0 || station->passengers_to_board <= 0){
    pthread_cond_wait(&station->cond, &station->mutex);
  }
  station->waiting_passengers--;
  station->available_seats--;
  station->passengers_to_board--;
  pthread_mutex_unlock(&station->mutex);
}

void station_on_board(struct station *station) {
  pthread_mutex_lock(&station->mutex);
  station->passengers_boarded++;
  pthread_cond_broadcast(&station->cond);
  pthread_mutex_unlock(&station->mutex);
}
