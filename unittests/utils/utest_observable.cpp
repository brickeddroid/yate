#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <observablesubject.hpp>

class MockObserver : public Yate::Utils::Observer {
public:
    virtual ~MockObserver() = default;
    virtual void callback(const Yate::Utils::Event& event){

    }
};

class MockOfTheMockObserver : public MockObserver {
public:

    MOCK_METHOD(void, callback, (const Yate::Utils::Event& event));
};

// Stub needed to get access to the protected methods
class SubjectStub : public Yate::Utils::ObservableSubject {
public:
    using Yate::Utils::ObservableSubject::emit_event;
};

TEST(UtilsTest, AsyncObserverCallbackAssertion){
    SubjectStub s;
    std::shared_ptr<MockOfTheMockObserver> observer = std::make_shared<MockOfTheMockObserver>();

    s.register_observer("unit_test_callback", &MockOfTheMockObserver::callback, observer);

    EXPECT_CALL(*observer, callback(Yate::Utils::Event("unit_test_callback")))
            .WillOnce(testing::Return());

    s.emit_event("unit_test_callback");

    s.unregister_observer("unit_test_callback", observer);

    s.emit_event("unit_test_callback");
}
