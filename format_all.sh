#!/bin/bash

echo "=== Форматирование всех C++ файлов рекурсивно ==="

# Находим и форматируем все .cpp и .h файлы
while IFS= read -r file; do
    clang-format -i "$file"
done < <(find . -type f \( -name "*.cpp" -o -name "*.h" -o -name "*.hpp" \) ! -path "./build/*" ! -path "./.*")

echo "=== Готово! ==="
