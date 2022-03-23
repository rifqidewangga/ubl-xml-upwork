#include "QRGenerator.h"

std::string QRGenerator::GenerateQRString(QRCodeData qr)
{
	std::stringstream qr_stream;
	
	qr_stream << GenerateTLVHex(qr.SellersName.Tag, qr.SellersName.Value);
	qr_stream << GenerateTLVHex(qr.VATNumber.Tag, qr.VATNumber.Value);
	qr_stream << GenerateTLVHex(qr.Timestamp.Tag, qr.Timestamp.Value);
	qr_stream << GenerateTLVHex(qr.InvoiceTotal.Tag, qr.InvoiceTotal.Value);
	qr_stream << GenerateTLVHex(qr.VATTotal.Tag, qr.VATTotal.Value);

	return TLVHexToBase64(qr_stream.str());
}

std::string QRGenerator::GenerateTLVHex(std::string tag, std::string value)
{
	std::stringstream hex_string_stream;
	hex_string_stream << tag;
	hex_string_stream << std::setfill('0') << std::setw(2) << std::hex << value.size();

	CkBinData bd_string;
	bd_string.AppendString(value.c_str(), "utf-8");
	hex_string_stream << bd_string.getEncoded("Hex");

	return hex_string_stream.str();
}

std::string QRGenerator::TLVHexToBase64(std::string tlv_hex)
{
	CkBinData bd_hex;
	bd_hex.AppendEncoded(tlv_hex.c_str(), "Hex");
	const char* base64_s = bd_hex.getEncoded("Base64");

	return base64_s;
}
