@echo off
cd /d "C:\project\Cafe_manage"

echo 🔄 Compiling the project...
g++ main.cpp Cafeteria.cpp User.cpp FoodItem.cpp OrderItem.cpp -o main.exe

if exist main.exe (
    echo ✅ Compilation successful.
    echo 🏃‍♂️ Running Cafeteria System...
    main.exe
) else (
    echo ❌ Compilation failed.
    pause
)
pause
