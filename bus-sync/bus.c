// Fill in empty functions and defintions

#include "pintos_headers.h"

struct station {

    int passengerNum;
    struct lock lockBus;
    struct condition cond_busLoading;
    struct condition cond_passengerBoarding;

};

void station_setup(struct station *station) {
	station->passengerNum = 0;
	lock_init(&station->lockBus);
	cond_init(&station->cond_busLoading);
	cond_init(&station->cond_passengerBoarding);
}

void bus_load_passengers(struct station *station, int count) {
    lock_acquire(&station->lockBus);

    while (count > 0 && station->passengerNum > 0)
    {
        cond_signal(&station->cond_busLoading, &station->lockBus);
        count--;
        station->passengerNum--;
        cond_wait(&station->cond_passengerBoarding, &station->lockBus);
    }

    lock_release(&station->lockBus);
}

void passenger_waitfor_bus(struct station *station) {
    lock_acquire(&station->lockBus);

    station->passengerNum++;
    cond_wait(&station->cond_busLoading, &station->lockBus);
    
    lock_release(&station->lockBus);
}

void passenger_on_board(struct station *station) {
    lock_acquire(&station->lockBus);    
    cond_signal(&station->cond_passengerBoarding, &station->lockBus);
    lock_release(&station->lockBus);
}
