
//
//  Copyright © 2016 Project Llama. All rights reserved.
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//

#include "benchmark/benchmark.h"

#include "Sort/BruteForceSort.h"
#include "Sort/InsertionSort.h"

static void StdSortInt(benchmark::State& state) {
    std::vector<int> a = {5, 4, 3, 2, 1};
    while (state.KeepRunning()) {
        std::sort(a.begin(), a.end());
    }
}

static void StdSortString(benchmark::State& state) {
    std::vector<std::string> a = {"5", "4", "3", "2", "1"};
    while (state.KeepRunning()) {
        std::sort(a.begin(), a.end());
    }
}

// Sorting with BruteForce Sort.
static void BFSortInt(benchmark::State& state) {
    llama::BruteForceSort<int> bfSort = llama::BruteForceSort<int>();
    std::vector<int> a = {5, 4, 3, 2, 1};
    while (state.KeepRunning()) {
        bfSort.performSort(&a);
    }
}

static void BFSortString(benchmark::State& state) {
    llama::BruteForceSort<std::string> bfSort = llama::BruteForceSort<std::string>();
    std::vector<std::string> a = {"5", "4", "3", "2", "1"};
    while (state.KeepRunning()) {
        bfSort.performSort(&a);
    }
}

static void BFSortDouble(benchmark::State& state) {
    llama::BruteForceSort<double> bfSort = llama::BruteForceSort<double>();
    std::vector<double> a = {5.0, 4.0, 3.0, 2.0, 1.0};
    while (state.KeepRunning()) {
        bfSort.performSort(&a);
    }
}

// Sorting with Insertion Sort.
static void InSortInt(benchmark::State& state) {
    llama::InsertionSort<int> inSort = llama::InsertionSort<int>();
    std::vector<int> a = {5, 4, 3, 2, 1};
    while (state.KeepRunning()) {
        inSort.performSort(&a);
    }
}

static void InSortString(benchmark::State& state) {
    llama::InsertionSort<std::string> inSort = llama::InsertionSort<std::string>();
    std::vector<std::string> a = {"5", "4", "3", "2", "1"};
    while (state.KeepRunning()) {
        inSort.performSort(&a);
    }
}

static void InSortDouble(benchmark::State& state) {
    llama::InsertionSort<double> inSort = llama::InsertionSort<double>();
    std::vector<double> a = {5.0, 4.0, 3.0, 2.0, 1.0};
    while (state.KeepRunning()) {
        inSort.performSort(&a);
    }
}

class CustomisedClass {
public:
    CustomisedClass() {}
    CustomisedClass(int input) {
        this->input = input*10;
    }

    int getInput() const {
        return input;
    }

    operator std::string() const
    {
        return "CustomisedClass: "+std::to_string(getInput());
    }

private:
    int input;
};
namespace llama {
template<>
int SortObject<CustomisedClass>::compare(SortObject<CustomisedClass> comparedObject) const {
    return obj.getInput() - comparedObject.getObj().getInput();
}
}  // namespace llama

static void BFSortClass(benchmark::State& state) {
    llama::BruteForceSort<CustomisedClass> bfSort = llama::BruteForceSort<CustomisedClass>();
    std::vector<CustomisedClass> a = {CustomisedClass(5), CustomisedClass(4),
                          CustomisedClass(3), CustomisedClass(2), CustomisedClass(1)};
    while (state.KeepRunning()) {
        bfSort.performSort(&a);
    }
}

static void InSortClass(benchmark::State& state) {
    llama::InsertionSort<CustomisedClass> inSort = llama::InsertionSort<CustomisedClass>();
    std::vector<CustomisedClass> a = {CustomisedClass(5), CustomisedClass(4),
                          CustomisedClass(3), CustomisedClass(2), CustomisedClass(1)};
    while (state.KeepRunning()) {
        inSort.performSort(&a);
    }
}

BENCHMARK(StdSortInt);
BENCHMARK(StdSortString);
BENCHMARK(BFSortInt);
BENCHMARK(BFSortString);
BENCHMARK(BFSortDouble);
BENCHMARK(BFSortClass);
BENCHMARK(InSortInt);
BENCHMARK(InSortString);
BENCHMARK(InSortDouble);
BENCHMARK(InSortClass);

BENCHMARK_MAIN();
