#include "Transaction.h"


ostream& operator<<(ostream& os, const Transaction& t)
{
    os << setw(5) <<t.id << ": " << setw(5) <<((t.Ttype == Transaction::type::BUY) ? "BUY " : "SELL ") <<setw(10)<< t.stock->getName() << " " <<setw(7)<<left << t.amount << " "<< setw(7)<<left << t.price << " ";
    return os;
}
