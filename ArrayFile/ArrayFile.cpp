 // ArrayFile.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <ios>
#include <vector>

#include <time.h>

// Оголошуємо функції для їх використання
bool IsError(int Data, int MaxX); // перевірка на вірно введені дані
int ConsoleInputSizeArray(const int sizeMax); // Введення розміру масиву
int ConsoleInputArray(int sizeMax, int*& A); // Введення масиву руками
int MainInput();
int RndInputArray(int sizeMax, int*& A); // Введення масиву автоматично
void WriteArrayTextFile(int n, int* arr, const char* fileName); // Запис масиву в текст. файл
int ReadArrayTextFile(int*& arr, const char* fileName); // Читаємо текстовий файл


using namespace std;

typedef double* pDouble;
//**********************************************************************
// Введення розміру масиву з обмеженням максимальної кількості елементів
//**********************************************************************
int ConsoleInputSizeArray(const int sizeMax)
{
    int size = 0; 
    do {
        cout << "Input size Array ( 0 < n <= " << sizeMax << " ) n = ";
        cin >> size;

    } while (not IsError(size, sizeMax));
    return size;
}
//*********************************************************
// Перевірити чи введене ціле число
//*********************************************************
bool IsError(int Data, int MaxX)
{
    if (cin.fail())  // якщо введене не ціле число
    {
        cout << "*** Incorect, please make a new choice\n";
        cin.clear();              // скинути стан помилки
        cin.ignore(1000, '\n');   // очистити буфер
    }
    else if (MaxX > 0) // якщо ціле то перевірити 0 < Data < MaxX (MaxX = 0 не перевіряти)
    {
        if (Data >= 0 && Data < MaxX) {
            return true; // Все Ок
        }
        else {
            cout << "*** Incorect, please make a new choice\n";
        }
    }
    return false; // Повторити ввод
}
//*********************************************************
// Задати алгоритм отримання масиву
//*********************************************************
int MenuInput()
{
    int i;
    do {
        cout << "     Menu Input   \n";
        cout << "    1.  Console all \n";
        cout << "    2.  Console - size, array - random \n";
        cout << "    3.  FileArray1.txt \n";
        cout << "    0.  Exit \n";

        cin >> i; // ввести позицію меню

    } while (not IsError(i, 4));
    return i;
}
//**********************************************************************
// Введення заданого масива цілих чисел з консолі
//**********************************************************************
int ConsoleInputArray(int*& A, int sizeMax)
{
    int n = ConsoleInputSizeArray(sizeMax);
    A = new int[n];
    for (int i = 0; i < n; i++) {
        cout << " Array[ " << i << "] "; cin >> A[i];
    }
    return n;
}
//**********************************************************************
// Введення заданого масива автоматично рандомно від 0 до 100
//**********************************************************************
int RndInputArray(int sizeMax, int*& A)
{
    int size = ConsoleInputSizeArray(sizeMax);
    int r1=0;
    A = new int[size];
    // виконуємо для того щоб не повторювалися числа які гернеруються рандомно
    srand(time(nullptr));

    for (int i = 0; i < size; i++) {
        r1 = rand();
        A[i] = r1 % 100;
    }
    return size;
}
//**************************************************************************
// запис масива в текстовий файл
//**************************************************************************
void WriteArrayTextFile(int n, int* arr, const char* fileName)
{
    ofstream fout(fileName);
    if (fout.fail()) return;
    fout << n << endl;
    for (int i = 0; i < n; i++) {
        fout << arr[i] << "   ";
    }

    fout.close(); //
}
//**************************************************************************
// читаємо масив з текстового файла
//**************************************************************************
int ReadArrayTextFile(int*& arr, const char* fileName)
{
    int size;
    ifstream fin(fileName);
    if (fin.fail()) return 0;
    fin >> size;
    arr = new int[size];

    if (size <= 0) return 0;
    for (int i = 0; i < size; i++)
        fin >> arr[i];
    fin.close();
    return size;

}
//**************************************************************************
int ConsoleInputDynamicArrayNew(int sizeMax, pDouble &pA)
{
    int size = ConsoleInputSizeArray(sizeMax);
    pA = new double[size];
    if (pA == nullptr) { return 0; }
    for (int i = 0; i < size; i++) {
        cout << " Array[ " << i << "] "; cin >> pA[i];
    }
    return size;
}

int ConsoleInputDynamicArray_calloc(int sizeMax, pDouble& pA)
{
    int size = ConsoleInputSizeArray(sizeMax);
    pA = (double*)calloc(size, sizeof(double));      // pA = (double*)malloc(size * sizeof(double)); 
    if (pA == nullptr) { return 0; }
    for (int i = 0; i < size; i++) {
        cout << " Array[ " << i << "] "; cin >> pA[i];
    }
    return size;
}

void ConsoleInputVector(int sizeMax, vector<double> &A)
{
    int size = ConsoleInputSizeArray(sizeMax);
    double d;
    for (int i = 0; i < size; i++) {
        cout << " Array[ " << i << "] "; cin >> d; A.push_back(d);
    }
    return ;
}


void WriteArrayBinFile(int n, double* arr, const char* fileName)
{
    //ios_base
    ofstream bfout(fileName, ios_base::binary);
    if (bfout.fail()) return;
    bfout.write((const char*)&n, sizeof(int));
    std::streamsize  cn = static_cast<std::streamsize>(n) *sizeof(double);
    bfout.write((const char*)arr, cn);
    bfout.close();
}

int ReadArrayBinFile(int n, double* arr, const char* fileName)
{
    int size=0;
    ifstream bfin(fileName, ios_base::binary);
    if (bfin.fail()) return 0;
    bfin.read((char*)&size, sizeof(int));
    if (size <= 0) return 0;
    if (size > n) size = n;
    bfin.read((char*)arr, static_cast<std::streamsize>(size) * sizeof(double));
    bfin.close();
    // ssdhs
    return size;
}

void ShowMainMenu()
{
    cout << "    Main Menu  \n";
    cout << "    1.  Task 1  \n";
    cout << "    2.  Task 2  \n";
    cout << "    3.  Task 3  \n";
  }

void MenuTask()
{
    cout << "     Menu Task   \n";
    cout << "    1.  Local array  \n";
    cout << "    2.  Dynamic array 1 \n";
    cout << "    3.  Dynamic array 2  new \n"; 
    cout << "    4.  Dynamic array : vector \n";
    cout << "    5.  Exit \n";
}

int main()
{   
    int i;
    int* B = nullptr;
    int* Rd = nullptr;
    int n = 0;
    const char* txtFile="Array_1.txt";
    
  //  n = RndInputArray(300, B);
  //  cout << "Array of " << n << " Ок " << endl;
 //   for (int i = 0; i < n; i++)
  //      cout << B[i] << " ";
   // cout << endl << " Write to txt file " << endl;

   // WriteArrayTextFile(n, B, txtFile);

    n = ReadArrayTextFile(Rd, txtFile);
    cout << "Array of " << n << " Ok " << endl;
    for (int i = 0; i < n; i++)
        cout << Rd[i] << " ";


    return 1;

}

    // Завдання 1, варіант 7
    // Із одновимірного масиву А розміру N побудувати масив 
    // В із елементів, які більші числа 10
   
    // i = MenuInput(); // Вибор алгоритму роботи
   // n = ConsoleInputArray(B, 300);







    /*
    const int MAX_SIZE = 560;
    std::cout << "Hello World!\n";
    ShowMainMenu();
    
    double A[MAX_SIZE], B[MAX_SIZE],C[MAX_SIZE];
    int n,m;
    n = RndInputArray(MAX_SIZE, A);
    WriteArrayTextFile(n, A, "1.txt");
    m = ReadArrayTextFile(MAX_SIZE, B, "1.txt");
    cout << " \n m= " << m << endl;
    for (int i = 0; i < m; i++)
        cout << B[i] << "   ";
    WriteArrayBinFile(n, A, "1.bin");
    m = ReadArrayBinFile(MAX_SIZE, C, "1.bin");
    cout << " \n m= " << m << endl;
    for (int i = 0; i < m; i++)
        cout << C[i] << "   ";
    cout << "\n  Vector \n";
    vector<double> vA;
    ConsoleInputVector(MAX_SIZE, vA);
    for (auto v : vA) {
        cout << v << "   ";
    } 

    TaskV();*/


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
