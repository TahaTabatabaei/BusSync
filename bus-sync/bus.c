// Fill in empty functions and defintions

#include "pintos_headers.h"

struct station {

    int passengerNum = 0;
    lock lockBus;
    condition cond_busLoading;
    condition cond_passengerBoarding;

};

void station_setup(struct station *station) {
    lock_acquire(&station->lockBus);

    while (count > 0 && station->passengers > 0)
    {
        cond_signal(&station->cond_busLoading, &station->lockBus);
        count--;
        station->passengers--;
        cond_wait(&station->cond_passengerBoarding, &station->lockBus);
    }

    lock_release(&station->lockBus);
}

void bus_load_passengers(struct station *station, int count) {

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
