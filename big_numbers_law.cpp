/*
 * @Author: Ivan Chichvarin ichichvarin@humanplus.ru
 * @Date: 2024-03-27 23:19:41
 * @LastEditors: Ivan Chichvarin ichichvarin@humanplus.ru
 * @LastEditTime: 2024-03-31 13:26:44
 * @FilePath: /big_numbers_law/big_numbers_law.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <cstdlib>
#include <chrono>
#include <iostream>
#include "log_duration.h"
#include <vector>

using namespace std;
using namespace chrono;

vector<int> ReverseVector(const vector<int>& source_vector) {
    vector<int> res;
    for (int i : source_vector) {
        res.insert(res.begin(), i);
    }

    return res;
}

vector<int> ReverseVector2(const vector<int>& source_vector) {
    vector<int> res;

    // будем проходить source_vector задом наперёд
    // с помощью обратного итератора
    for (auto iterator = source_vector.rbegin(); iterator != source_vector.rend(); ++iterator) {
        res.push_back(*iterator);
    }

    return res;
} 

vector<int> ReverseVector3(const vector<int>& source_vector) {
    vector<int> res;
    res.reserve(source_vector.size());

    // будем проходить sourceVector задом наперёд
    // с помощью обратного итератора
    for (auto iterator = source_vector.rbegin(); iterator != source_vector.rend(); ++iterator) {
        res.push_back(*iterator);
    }

    return res;
} 

int CountPops(const vector<int>& source_vector, int begin, int end) {
    int res = 0;

    for (int i = begin; i < end; ++i) {
        if (source_vector[(size_t)i]) {
            ++res;
        }
    }

    return res;
}

void AppendRandom(vector<int>& v, int n) {
    v.reserve(v.size()+(size_t)n);
    for (int i = 0; i < n; ++i) {
        // получаем случайное число с помощью функции rand.
        // с помощью (rand() % 2) получим целое число в диапазоне 0..1.
        // в C++ имеются более современные генераторы случайных чисел,
        // но в данном уроке не будем их касаться
        v.push_back(rand() % 2);
    }
}

void AppendRandom2(vector<int>& v, int n) {
    v.reserve(v.size()+(size_t)n);
    for (int i = 0; i < n; i += 15) {
        int number = rand();

        // мы можем заполнить 15 элементов вектора,
        // но не более, чем нам осталось до конца:
        int count = min(15, n - i);

        for (int j = 0; j < count; ++j)
            // таким образом, получим j-й бит числа.
            // операцию побитового сдвига вы уже видели в этой программе
            // на этот раз двигаем вправо, чтобы нужный бит оказался самым последним
            v.push_back((number >> j) % 2);
    }
}

void Operate() {
    vector<int> random_bits;
    LOG_DURATION("Total");
    // операция << для целых чисел это сдвиг всех бит в двоичной
    // записи числа. Запишем с её помощью число 2 в степени 17 (131072)
    static const int N = 1 << 25;

    {
        LOG_DURATION("Append random");
        // заполним вектор случайными числами 0 и 1
        AppendRandom2(random_bits, N);
    } 
    
    vector<int> reversed_bits;

    {
        LOG_DURATION("Reverse");
        // перевернём вектор задом наперёд
        reversed_bits = ReverseVector3(random_bits);
   
    } 
    
    {
        LOG_DURATION("Counting");
        // посчитаем процент единиц на начальных отрезках вектора
        for (int i = 1, step = 1; i <= N; i += step, step *= 2) {
            // чтобы вычислить проценты, мы умножаем на литерал 100. типа double;
            // целочисленное значение функции CountPops при этом автоматически
            // преобразуется к double, как и i
            double rate = CountPops(reversed_bits, 0, i) * 100. / i;
            cout << "After "s << i << " bits we found "s << rate << "% pops"s << endl;
        }
    }
    
    
}

int main() {
    Operate();
    return 0;
}