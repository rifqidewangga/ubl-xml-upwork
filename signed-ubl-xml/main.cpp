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
    Invoice invoice;
    invoice.ID = 1;
    invoice.UUID = "3cf5ee18-ee25-44ea-a444-2c37ba7f28be";
    invoice.IssueDate = "2021-02-25";
    invoice.IssueTime = "16:55:24";

    invoice.BillingReferenceID = "156166151";
    
    invoice.AdditionalReference1_UUID = "70";
    invoice.PIH = "NWZlY2ViNjZmZmM4NmYzOGQ5NTI3ODZjNmQ2OTZjNzljMmRiYzIzOWRkNGU5MWI0NjcyOWQ3M2EyN2ZiNTdlOQ==";
    invoice.QRCode = "AQpGaXJzdCBTaG9wAg8zMTAxODkzNzU5MjAwMDMDFDIwMjEtMDEtMDVUMDk6MzI6NDBaBAYyNTAuMDAFBDAuMDAGQDhiMGE1Zjk5YWQ2MjEzZjVmZGJhM2YyZGI4Zjk4OWZiOTkyYzBhYjQ4NmEyOTIyYjIyMWIxNWJjODYzODlkNWEHsDMwNTYzMDEwMDYwNzJhODY0OGNlM2QwMjAxMDYwNTJiODEwNDAwMGEwMzQyMDAwNDk2ZThjNDk0MDNmYzA5NDVjOGY0MDI1OGNkZDJkOWU5MzAxYTc5MjEyYTkzYTdjOGZmYWQ4ZWMyZDgxNWMyNWYyY2I0ZGQ1ZmU1M2ZiOGU3ZDBiNGEwMjZmY2E0NTcyMzUxM2Q3N2MwZTMzOGU5MTUxNjhlNTBkNTk0MDRkYjk0CCBnn5Fhp6qCOBB+MMZTOU3/U3wGIVpnvGnJURw/1cYJ2gkgAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA=";
    
    invoice.InstructionNote = "Some notes";

    invoice.TaxAmount = 0.0;
    invoice.TaxableAmount = 0.0;
    invoice.VATPercent = 0.0;
    
    invoice.LineExtensionAmount = 250.0;
    invoice.TaxExclusiveAmount = 250.0;
    invoice.TaxInclusiveAmount = 250.0;
    invoice.PayableAmount = 250.0;

    InvoiceLine invoiceLine;
    invoiceLine.ID = "18373428";
    invoiceLine.Quantity = 1;
    invoiceLine.LineExtensionAmount = 250.0;
    invoiceLine.Name = "Chocolate";
    invoiceLine.PriceAmount = 250.0;
    invoiceLine.TaxAmount = 0.0;
    invoiceLine.RoundingAmount = 250.0;

    invoice.InvoiceLines.push_back(invoiceLine);

    InvoiceGenerator gen("../Samples/certs/gaztCertificate.p12", "123456789");
    gen.Generate(invoice, "../Samples/signedDoc.xml");

    return 0;
}