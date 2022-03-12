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
	double TaxAmount;
	double RoundingAmount;
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
	std::string QRCode = "AQpGaXJzdCBTaG9wAg8zMTAxODkzNzU5MjAwMDMDFDIwMjEtMDEtMDVUMDk6MzI6NDBaBAYyNTAuMDAFBDAuMDAGQDhiMGE1Zjk5YWQ2MjEzZjVmZGJhM2YyZGI4Zjk4OWZiOTkyYzBhYjQ4NmEyOTIyYjIyMWIxNWJjODYzODlkNWEHsDMwNTYzMDEwMDYwNzJhODY0OGNlM2QwMjAxMDYwNTJiODEwNDAwMGEwMzQyMDAwNDk2ZThjNDk0MDNmYzA5NDVjOGY0MDI1OGNkZDJkOWU5MzAxYTc5MjEyYTkzYTdjOGZmYWQ4ZWMyZDgxNWMyNWYyY2I0ZGQ1ZmU1M2ZiOGU3ZDBiNGEwMjZmY2E0NTcyMzUxM2Q3N2MwZTMzOGU5MTUxNjhlNTBkNTk0MDRkYjk0CCBnn5Fhp6qCOBB+MMZTOU3/U3wGIVpnvGnJURw/1cYJ2gkgAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA=";

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
};