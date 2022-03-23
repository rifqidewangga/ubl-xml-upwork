#pragma once

#include <sstream>
#include <iomanip>
#include <chrono>
#include <fstream>
#include <iostream>

#include <CkXml.h>
#include <CkStringBuilder.h>
#include "Invoice.h"
#include "XMLSigner.h"
#include "QRGenerator.h"
#include "Utility.h"

#define PIH_TEMP_FILENAME "pih.txt"

#define SELLER_NAME "DCCF"
#define SELLER_VAT_NUMBER "300452385900003"

//#define CHILKAT_SIGNER
#define ZATCA_SDK_SIGNER

class InvoiceGenerator
{
public:
	InvoiceGenerator();
	void Generate(Invoice invoice, std::string filepath);

	std::string GetPIH();
	std::string GetQR();

private:
	CkXml xmlToSign;
	CkXml signedXml;
	QRGenerator qrGenerator;

	std::string lastXmlQR;
	
	std::string GetString(double val);

	void PopulateXml(Invoice invoice);

	void CheckInvoiceType(Invoice invoice);
	void InitializeEmptyXml();
	void PopulateUBLExt(Invoice invoice);
	void PopulateBasicInfo(Invoice invoice);
	void PopulateDocumentReferences(Invoice invoice);
	void PopulateSupplierPartyInfo();
	void PopulateCustomerPartyInfo(Invoice invoice);
	void PopulateDeliveryDate(Invoice invoice);
	void PopulatePatmentMeans(Invoice invoice);
	void PopulateTaxTotal(Invoice invoice);
	void PopulateLegalMonetaryTotal(Invoice invoice);
	void PopulateInvoiceLines(Invoice invoice);

	void InjectQRCode(Invoice invoice);

	void SaveXmlToSign(std::string path);
	void SaveSignedXml(std::string path);

	void SignXMLZatcaSDK(std::string filename);
	void SignXMLChilkat(std::string filename);

	void UpdateLastQR();
	void UpdatePIH();
};
