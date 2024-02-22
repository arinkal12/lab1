
#include <iostream>
#include <random>
const int MAX_SIZE = 3;
using namespace std;
void vivod_matrix(float** A, float* b, int n) { // вывод матрицы в нужном формате рис 3.1
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << A[i][j] << "\t";
        }
        cout << "|x" << i<< "|"<<b[i] << endl;
    }
}
void vvod_rucami(float** A, float* b, int n){ //заполнение матрицы с клавиатуры
    cout << "vvedite el matrix A:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "A[" << i + 1 << "][" << j + 1 << "]: ";
            cin >> A[i][j];
        }
    }

    cout << "vvedite el vektora b:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "b[" << i + 1 << "]: ";
        cin >> b[i];
    }
}
void rand_zap(float** A, float* b, int n){// заполнение псведослучайными числами
    int max,min;
    cout << "vvedite verx and niz gran generacii";
    cin >>max;
    cin >>min;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(min, max);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j]=dis(gen);
        }
    }
    for (int i = 0; i < n; i++) {
        b[i]=dis(gen);
    }

}

void pram_xod(float** A, float* b, int n) {// прямой ход с главным элементом 
    
    for (int i = 0; i < n; i++) {//поиск и перестановка строк для ненулевого элемента
        if (A[i][i] == 0) {
            for (int k = i + 1; k <n; k++) {
                if (A[k][i] != 0) {//меняем строчки местами 
                    swap(A[k], A[i]);
                    swap(b[k], b[i]);
                    break;
                }
            }
        }
        for (int k = i + 1; k < n; k++) {//деление строчки на главный элемент и вычитание строк
            double obnyl = A[k][i] / A[i][i];
            for (int j = i; j < n; j++) {
                A[k][j] -= obnyl * A[i][j];
            }
            b[k] -= obnyl * b[i];
        }
    }
}
void obratn_xod(float** A, float* b, float* x, int n) {

    for (int i = n - 1; i >= 0; i--) {//начинаем цикл с последнего элемента системы и идем в обратном порядке
        double q = b[i];// устанавливаем начальное значение для ку 
        for (int j = i + 1; j < n; j++) {
            q -= A[i][j] * x[j];
        }
        x[i] = q / A[i][i];
    }
}
void vektor_nevazki(float** A, float* b,float* x,float* nevazki, int n) {// нахождения вектора невязки 
    for (int i = 0; i < n; i++) {
        nevazki[i] = b[i];
        for (int j = 0; j < n; j++) {
            nevazki[i] -= A[i][j] * x[j];
        }
    }
}
void print_vektor_nevazki(float* nevazki, int n){//вывод вектора невязки
    for (int i =0; i<n; i++) {
        cout << "U" << i+1 << "= " << nevazki[i] <<endl;
    }
    
}


// сохранить копию матрицы А

int main() {
    int vibor = 0;
    int n;//задание размера системы линейных уравнений
    cout << "vvedite razmer cictemi lin yr (n): ";// введите размер системы линейных ур
    cin >> n;
    if (n > MAX_SIZE) { 
        cout << "error" << endl;
        return 1;
    }
    float**A = new float*[n];
    for(int i = 0;i < n; i++){
        A[i] = new float[n];
    }
    float* b = new float[n];
    float* x = new float[n];//решения
    float* nevazki= new float[n];
    
    float** A_copy = new float*[n];
    for (int i = 0; i < n; i++) {
        A_copy[i] = new float[n];
        for (int j = 0; j < n; j++) {
            A[i][j] = A_copy[i][j];
        }
    }

    float* b_copy = new float[n];
    for (int i = 0; i < n; i++) {
        b[i] = b_copy[i];
    }
    

    cout << "kak zapolnit matrix: 1- esli rykami, 2 - esli random ";// выбор  как заполинить массив 
    cin>> vibor;
    if (vibor == 1){
        vvod_rucami(A, b, n);
    }
    else if (vibor == 2)
    {
        rand_zap(A, b, n);
    }
    else {
        cout << "error";
    }
    
    //cout << "Исходная система уравнений A*x=b:" << endl;
    pram_xod(A,b,n);
    obratn_xod(A, b, x, n);
    cout << "res:" << endl;// вывод результата 
    for (int i = 0; i < n; i++) {
        cout << "x" << i+1<< "="<<x[i]<< " "<< endl;
    }
    //чистим память 
   for (int i = 0; i < MAX_SIZE; i++) {
        delete[] A[i];
        delete[] A_copy[i];
   }
    delete[] A;
    delete[] b;
    delete[] x;
    delete[] A_copy;
    delete[] b_copy;

    return 0;
}