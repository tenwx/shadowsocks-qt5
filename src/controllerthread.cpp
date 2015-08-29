#include "controllerthread.h"

ControllerThread::ControllerThread(QObject *parent) :
    QThread(parent)
{}

QMutex ControllerThread::mutex;

void ControllerThread::setup(bool _debug, const QSS::Profile &_profile)
{
    debug = _debug;
    profile = _profile;
}

void ControllerThread::run()
{
    mutex.lock();
    QSS::Controller controller(true);
    connect(&controller, &QSS::Controller::runningStateChanged, this, &ControllerThread::stateChanged);
    connect(&controller, debug ? &QSS::Controller::debug : &QSS::Controller::info, this, &ControllerThread::logAvailable);
    connect(&controller, &QSS::Controller::newBytesReceived, this, &ControllerThread::newBytes);
    connect(&controller, &QSS::Controller::newBytesSent, this, &ControllerThread::newBytes);
    controller.setup(profile);
    bool started = controller.start();
    mutex.unlock();
    if (started) {
        exec();
    } else {
        emit failed();
    }
}
