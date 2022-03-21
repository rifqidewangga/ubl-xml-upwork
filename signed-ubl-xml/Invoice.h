#pragma once

#include <string>
#include <vector>

enum InvoiceType
{
	Simplified	= 0,
	Standard	= 1
};

struct InvoiceLine
{
	std::string ID;
	int Quantity;
	double LineExtensionAmount;
	std::string Name;
	double PriceAmount;
	double TaxAmount;
	double RoundingAmount;
};

struct CustomerParty
{
	// all of values are default to simplified xml
	std::string SchemeID = "NAT";
	std::string ID = "1010101010";
	std::string StreetName = "Prince Migrin st";
	std::string BuildingNumber = "7796";
	std::string PlotIdentification = "4451";
	std::string CitySubdivisionName = "Labor City";
	std::string CityName = "Khobar";
	std::string PostalZone = "34441";
	std::string CountrySubentity = "Eastern Province";
	std::string RegistrationName = "Walk In Customer";
};

struct Invoice
{
	InvoiceType Type;

	int ID;
	std::string UUID;
	std::string IssueDate;
	std::string IssueTime;

	std::string BillingReferenceID;

	std::string AdditionalReference1_UUID;
	std::string PIH;

	std::string PaymentMeansCode;
	std::string InstructionNote;

	double TaxAmount;
	double TaxableAmount;
	double VATPercent;

	double LineExtensionAmount;
	double TaxExclusiveAmount;
	double TaxInclusiveAmount;
	double PayableAmount;

	std::vector<InvoiceLine> InvoiceLines;

	CustomerParty CustomerParty;
};