#pragma once

#include <string>
#include <vector>

struct InvoiceLine
{
	std::string ID;
	int Quantity;
	double LineExtensionAmount;
	std::string Name;
	double PriceAmount;
};

struct Invoice
{
	int ID;
	std::string UUID;
	std::string IssueDate;
	std::string IssueTime;

	std::string BillingReferenceID;

	std::string AdditionalReference1_UUID;
	std::string PIH;
	std::string QRCode;

	std::string InstructionNote;

	double TaxAmount;
	double TaxableAmount;
	double VATPercent;

	double LineExtensionAmount;
	double TaxExclusiveAmount;
	double TaxInclusiveAmount;
	double PayableAmount;

	std::vector<InvoiceLine> InvoiceLines;
};