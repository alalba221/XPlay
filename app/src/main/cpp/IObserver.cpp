//
// Created by zy on 7/19/2018.
//

#include "IObserver.h"
using namespace std;
//主题函数
void IObserver::AddObs(IObserver* obs){
    if(!obs) return;
    mux.lock();
    obss.push_back(obs);
    mux.unlock();

}

//通知所有观察者
void IObserver::Notify(XData data){
    mux.lock();
/*    for(int i=0;i<obss.size();i++){
        obss[i]->Update(data);
    }
*/
    vector<IObserver*>::iterator itor = obss.begin();
    while(itor!=obss.end()){
        (*itor)->Update(data);
        itor++;
    }

    mux.unlock();
}