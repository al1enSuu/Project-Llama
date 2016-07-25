
#ifndef BRUTE_FORCE_SORT_H
#define BRUTE_FORCE_SORT_H

#include "Sort.h"

namespace llama {
	template<class T>
	class BruteForceSort : Sort<T> {
	public:
		BruteForceSort(std::vector<T> *inputArray) : Sort<T>(inputArray) { }

		void doSort(std::vector<SortObject<T>> *reformedArray) override {
			std::vector<SortObject<T>> resultArray(reformedArray->size(), SortObject<T>());
			for (int i = 0; i < reformedArray->size(); ++ i) {
				for (int j = 0; j < reformedArray->size(); ++ j) {
					if (reformedArray->at(i) > reformedArray->at(j)) {
						int index = j;
						while (!resultArray[index].na) {
							index ++;
						}
						index ++;
						resultArray[index] = reformedArray->at(i);

						break;
					}
				}
			}
			reformedArray = &resultArray;
		}
	};
}
#endif
