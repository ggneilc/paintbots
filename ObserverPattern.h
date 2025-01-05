#pragma once
#include <vector>
#include <memory>
#include <algorithm>


template<typename NotificationType>
class Observable;

template<typename NotificationType>
class Observer{
    public:
        virtual void update(const NotificationType& notification) = 0;
        virtual ~Observer() = default;

};

template<typename NotificationType>
class Observable{
    private:
        std::vector<Observer<NotificationType>*> observers;
    public:
        void addObserver(Observer<NotificationType>* observer){
            if (std::find(observers.begin(), observers.end(), observer) == observers.end())
                observers.push_back(observer);
        }
        void removeObserver(Observer<NotificationType>* observer){
            auto it = std::find(observers.begin(), observers.end(), observer);
            if (it != observer.end())
                observers.erase(it);
        }
        void notifyObservers(const NotificationType& notification){
            for (auto* observer : observers){
                observer->update(notification);
            }
        }
        virtual ~Observable() { observers.clear(); }

};

