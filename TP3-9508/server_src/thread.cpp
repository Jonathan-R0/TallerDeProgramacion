#include "thread.h"

#include <utility>

Thread::Thread() {}

Thread::~Thread() {}

void Thread::join() { thread.join(); }

void Thread::start() { thread = std::thread(&Thread::run, this); }

Thread::Thread(Thread&& other) { this->thread = std::move(other.thread); }

Thread& Thread::operator=(Thread&& other) {
  this->thread = std::move(other.thread);
  return *this;
}
