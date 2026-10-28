#ifndef SYNC_CAR_H
#define SYNC_CAR_H

#include <pthread.h>

struct station {
  pthread_mutex_t mutex;
  pthread_cond_t cond;

  int waiting_passengers;
  int available_seats;
  int passengers_to_board;
  int passengers_boarded;
  int car_present;
};

void station_init(struct station *station);
void station_load_car(struct station *station, int count);
void station_wait_for_car(struct station *station);
void station_on_board(struct station *station);

#endif
