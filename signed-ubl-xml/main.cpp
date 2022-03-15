#include <iostream>

#include <CkXml.h>
#include <CkXmlDSigGen.h>
#include <CkCert.h>
#include <CkStringBuilder.h>
#include <CkXmlDSig.h>

#include "Utility.h"
#include "XMLSigner.h"
#include "Invoice.h"
#include "InvoiceGenerator.h"


int main()
{
    InvoiceGenerator gen;

    Invoice invoice;
    invoice.ID = 1;
    invoice.UUID = "3cf5ee18-ee25-44ea-a444-2c37ba7f28be";
    invoice.IssueDate = "2022-03-15";
    invoice.IssueTime = "07:36:24";

    invoice.BillingReferenceID = "156166151";
    
    invoice.AdditionalReference1_UUID = "70";
    invoice.PIH = gen.GetPIH();
    
    invoice.PaymentMeansCode = "10";
    invoice.InstructionNote = "Some notes";

    invoice.TaxAmount = 33.0; // Total Tax from all invoicelines
    invoice.TaxableAmount = 220.0;
    invoice.VATPercent = 15.0;
    
    invoice.LineExtensionAmount = 220.0; // = Total of all invoice price without tax
    invoice.TaxExclusiveAmount = 220.0; // = LineExtensionAmount
    invoice.TaxInclusiveAmount = 253.0; // = TaxExclusiveAmount + TaxAmount
    invoice.PayableAmount = 253.0; // TaxInclusiveAmount

    InvoiceLine invoiceLine;
    invoiceLine.ID = "18373428";
    invoiceLine.Quantity = 1;
    invoiceLine.LineExtensionAmount = 220.0;
    invoiceLine.Name = u8"شكولاته حليب";
    invoiceLine.PriceAmount = 220.0;
    invoiceLine.TaxAmount = 33.0; // = VATPercent * LineExtensionAmount
    invoiceLine.RoundingAmount = 253.0; // = LineExtensionAmount + TaxAmount

    invoice.InvoiceLines.push_back(invoiceLine);

    gen.Generate(invoice, "../Samples/signedDoc.xml");

    std::cout << "QR: " << gen.GetQR() << std::endl;
    std::cout << "PIH: " << gen.GetPIH() << std::endl;

    return 0;
}
