#include <iostream>
#include <vector>
#include <cmath>
#include <string>

// Функция для определения количества столбцов
int calculateNumBins(int numNumbers) {
    int numBins;

    if (numNumbers == 0) {
        std::cerr << "Enter numbers: ";
        std::cin >> numNumbers;
    }

    double K = std::sqrt(numNumbers);

    if (K > 25) {
        numBins = 1 + static_cast<int>(std::log2(numNumbers));
        std::cerr << "The number of columns is selected according to the Sturges formula: " << numBins << std::endl; // Выбрано количество столбцов по формуле Стёрджеса:
    }
    else {
        numBins = static_cast<int>(K);
        std::cerr << "The number of columns is selected according to the empirical formula: " << numBins << std::endl; // Выбрано количество столбцов по эмпирической формуле:
    }

    return numBins;
}

// Функция для подсчета числа попавших в каждую корзину и вывода чисел в виде звездочек
std::vector<int> countBins(const std::vector<int>& numbers, int numBins, int& minVal, int& maxVal) {
    minVal = numbers[0];
    maxVal = numbers[0];

    for (int i = 1; i < numbers.size(); ++i) {
        if (numbers[i] < minVal)
            minVal = numbers[i];
        if (numbers[i] > maxVal)
            maxVal = numbers[i];
    }

    std::vector<int> counters(numBins, 0);
    double binSize = static_cast<double>(maxVal - minVal + 1) / numBins;

    for (int i = 0; i < numbers.size(); ++i) {
        int binIndex = static_cast<int>(std::floor((numbers[i] - minVal) / binSize));
        counters[binIndex]++;
    }

    return counters;
}

// Функция для преобразования суммы чисел в звездочки
std::string convertToStars(int count) {
    std::string stars;
    for (int i = 0; i < count; ++i) {
        stars += "*";
    }
    return stars;
}

// Функция для масштабирования звездочек
std::string scaleStars(int count, int maxCount, int maxWidth) {
    double scaleFactor = static_cast<double>(maxWidth) / maxCount;
    int scaledCount = static_cast<int>(std::round(count * scaleFactor));

    std::string stars;
    for (int i = 0; i < scaledCount; ++i) {
        stars += "*";
    }
    return stars;
}

int main() {
    int numNumbers;
    setlocale(LC_ALL, "rus");
    std::cerr << "Enter col-vo numbers: ";
    std::cin >> numNumbers;

    std::vector<int> numbers(numNumbers);
    std::cerr << "Enter numbers: ";
    for (int i = 0; i < numNumbers; ++i) {
        std::cin >> numbers[i];
    }

    int numBins = calculateNumBins(numNumbers);

    int minVal, maxVal;
    std::vector<int> binCounters = countBins(numbers, numBins, minVal, maxVal);

    std::cerr << "Range numbers: " << minVal << " - " << maxVal << std::endl; //диапозон чисел

    for (int i = 0; i < binCounters.size(); ++i) {
        std::cout << "Basket " << i + 1 << ": ";
        std::cout << convertToStars(binCounters[i]) << std::endl;
    }

    return 0;
}
