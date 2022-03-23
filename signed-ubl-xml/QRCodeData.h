#pragma once
#include <string>

struct QRData
{
	std::string Tag;
	std::string Value;

	QRData() = default;
	QRData(const char* tag, const char* value) : Tag(tag), Value(value) {};
};

struct QRCodeData
{
	QRData SellersName;
	QRData VATNumber;
	QRData Timestamp;
	QRData InvoiceTotal;
	QRData VATTotal;
	QRData HashOfXML;
	QRData ECDSASignature;
	QRData ECDSAPublicKey;
};