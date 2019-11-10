#ifndef ASYNC_H
#define ASYNC_H

#include <cstddef>
#include "bulk_builder/observer.h"

namespace async {

using handle_t = void *;
//установить приемника сообщений (по умолчанию сообщения выводячться в консоль)
//данная функция нужня для проведения юнит тестов
void set_observer(ObserverSPtr observer);
handle_t connect(std::size_t bulk);
void receive(handle_t handle, const char *data, std::size_t size);
void disconnect(handle_t handle);
//подождать пока очередь сообщений не станет пустой
//вызывающий поток заблокируется на вызове этой функции до тех пор пока
//в очереди сообщений не станет пусто. Если в момент вызова функции в очереди
//сообщений уже пусто тогда вызывающий поток разблокируется через время не более
//чем 1000 мс
void wait_queue_is_empty();

}  // namespace async

#endif  // ASYNC_H
