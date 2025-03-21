
#include "DataWrapper.h"
#include <cassert>
#include <fstream>
DataWrapper::DataWrapper() :
	fSize(0),
	fData(nullptr)
{};

DataWrapper::~DataWrapper() {
	delete [] fData; //why not delete this? 
}

bool DataWrapper::load(const std::string& aFileName) {
	//std::fstream myFile;
	//myFile.open(aFileName, std::ios::in);  // std::ifstream aInput (aFileName, std::ifstream::in);

	//while (!myFile.eof()) {
	//	DataMap aData;
	//	myFile >> aData;
	//	fData[fSize] = aData;
	//	fSize++;
	//}
	//return !(!myFile);
	bool Result = false;
	std::ifstream aInput(aFileName, std::ifstream::in);
	if (aInput) {
		if (aInput >> fSize) {  //read the fSize
			fData = new DataMap[fSize];
			for (int i = 0; i < fSize; i++) {
				aInput >> fData[i];  //read the inputs
			}
			Result = true;
		}
	}
	aInput.close();
	return Result;
}


size_t DataWrapper::size() const noexcept {
	return fSize;
}

const DataMap& DataWrapper::operator[] (size_t aIndex) const {
	assert(aIndex < fSize);
	return *((fData) + aIndex); //tutor used return fData[aIndex]
}