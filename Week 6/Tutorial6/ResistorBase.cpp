

#include <string>
#include "ResistorBase.h"

void ResistorBase::setBaseValue(double aValue) noexcept {
	fBaseValue = aValue;
}

ResistorBase::ResistorBase(double aBaseValue) noexcept {
	setBaseValue(aBaseValue);
}

double ResistorBase::getBaseValue() const noexcept {
	return fBaseValue;
}

double ResistorBase::getPotentialAt(double aCurrent, double aFrequency) const noexcept {
	return aCurrent * getReactance(aFrequency);
}

double ResistorBase::getCurrentAt(double aVoltage, double aFrequency) const noexcept {
	return aVoltage / getReactance(aFrequency);
}


std::istream& operator>>(std::istream& aIStream, ResistorBase& aObject) {
	double aBaseValue;
	std::string aUnit;

	aIStream >> aBaseValue >> aUnit;
	aObject.convertUnitValueToBaseValue(aBaseValue, aUnit);

	return aIStream;
}

std::ostream& operator<<(std::ostream& aOStream, const ResistorBase& aObject) {
	double aNormaliseValue;
	std::string aNormaliseUnit;

	aObject.convertBaseValueToUnitValue(aNormaliseValue, aNormaliseUnit);

	aOStream << aNormaliseValue << aNormaliseUnit;

	return aOStream;
}