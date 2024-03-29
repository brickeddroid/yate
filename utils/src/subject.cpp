#include "../subject.hpp"
//#include <observer.hpp>
namespace YateUtils {

template <class T>
void Subject<T>::notify(){
    for(auto const& observer_callback : m_observers){
        observer_callback(*this);
    }
}
}
