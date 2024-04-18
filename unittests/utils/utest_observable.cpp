#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <observablesubject.hpp>

class MockObserver {
public:
    virtual void callback(const Yate::Utils::Event& event){

    }
};

class MockOfTheMockObserver : public MockObserver {
public:

    MOCK_METHOD(void, callback, (const Yate::Utils::Event& event));
};


TEST(UtilsTest, AsyncObserverCallbackAssertion){
    Yate::Utils::ObservableSubject s;
    std::shared_ptr<MockOfTheMockObserver> observer = std::make_shared<MockOfTheMockObserver>();

    s.register_observer("unit_test_callback", &MockOfTheMockObserver::callback, observer);

    EXPECT_CALL(*observer, callback(Yate::Utils::Event("unit_test_callback")))
            .WillOnce(testing::Return());

    s.emit_event("unit_test_callback");

    s.unregister_observer("unit_test_callback", &MockOfTheMockObserver::callback, observer);

    s.emit_event("unit_test_callback");

}
