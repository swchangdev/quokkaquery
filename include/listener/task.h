#ifndef LISTENER_TASK_H_
#define LISTENER_TASK_H_

#include <future>

struct Task {
  // TODO: return the error code?
  std::future<int> result;
  bool active;
};

#endif /* LISTENER_TASK_H_ */