include "smart_ptr.h"

int main() {
    // Создание уникального указателя
    int* raw_ptr = (int*)malloc(sizeof(int));
    if (raw_ptr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    *raw_ptr = 42;

    // Упаковка в unique_ptr
    UniquePtr up = make_unique_ptr(raw_ptr);

    // Доступ к объекту
    printf("Value: %d\n", *(int*)get_unique_ptr(&up));

    // Перемещение владения
    UniquePtr new_up = move_unique_ptr(&up);
    
    // Проверка, что старый указатель больше не владеет объектом
    if (get_unique_ptr(&up) == NULL) {
        printf("Old unique_ptr is now null.\n");
    }

    // Пример вызова запрета на выделение памяти
    void* forbidden_memory = forbid_malloc(sizeof(int));
    if (forbidden_memory == NULL) {
        printf("Memory allocation was forbidden.\n");
    }

    // Освобождение памяти при завершении работы
    free_unique_ptr(&new_up);

    return 0;
}
