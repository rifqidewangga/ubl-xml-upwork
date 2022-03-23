#pragma once

#include <iostream>
#include <iomanip>
#include <sstream>

#include <CkBinData.h>

#include "QRCodeData.h"

class QRGenerator
{
public:
	std::string GenerateQRString(QRCodeData qr);

private:
	std::string GenerateTLVHex(std::string tag, std::string value);
	std::string TLVHexToBase64(std::string tlv_hex);
};

