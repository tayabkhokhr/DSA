/*  Data Structure and Algorithms
	Assignment # 2
	G1F23UBSCS184
	Tayyab Irfan
*/
#include<iostream>
#include<string>
using namespace std;
//class declaration
class DateNode;    
class DetailNode;  
class AmountNode;  
class IdNode
{
    public:
        int id;
        DateNode* next;  

        IdNode()
        {
            id=0;
            next=nullptr;
        }
};
class DateNode
{
    public:
        string date;
        DetailNode* next; 
        DateNode()
        {
            date="";
            next=nullptr;
        }
};
class DetailNode
{
    public:
        string detail;
        AmountNode* next;
        DetailNode()
        {
            detail="";
            next=nullptr;
        }
};
class AmountNode
{
    public:
        float amount;
        IdNode* next;  
        AmountNode()
        {
            amount=0;
            next=nullptr;
        }
};
class ExpenseTracker
{
    private:
        IdNode* head;
        int count;
        bool unique(int id)
        {
            IdNode* curr=head;
            while(curr!=nullptr)
			{
                if(curr->id==id) return false;
                AmountNode* amount=curr->next->next->next;
                curr=amount->next;
            }
            return true;
        }
    public:
        ExpenseTracker()
        {
            head=nullptr;
            count=0;
        }
        void addExpense()
        {
            if(count>=100) 
			{
                cout<<"Expense limit reached!\n";
                return;
            }

            IdNode* idNode=new IdNode();
            DateNode* dateNode=new DateNode();
            DetailNode* detailNode=new DetailNode();
            AmountNode* amountNode=new AmountNode();

            cout<<"Enter Expense ID (unique integer): ";
            cin>>idNode->id;
            cin.ignore();
            
            if(!unique(idNode->id))
			{
                cout<<"ID already exists!\n";
                delete idNode;
                delete dateNode;
                delete detailNode;
                delete amountNode;
                return;
            }

            cout<<"Enter Expense Date (DD-MM-YYYY): ";
            getline(cin,dateNode->date);

            cout<<"Enter Expense Detail: ";
            getline(cin,detailNode->detail);

            cout<<"Enter Expense Amount: ";
            cin>>amountNode->amount;
            cin.ignore();

            idNode->next=dateNode;
            dateNode->next=detailNode;
            detailNode->next=amountNode;
            amountNode->next=nullptr;

            if(head==nullptr) 
			{
                head=idNode;
            } 
			else
			{
                IdNode* curr=head;
                while(true) 
				{
                    AmountNode* lastAmount=curr->next->next->next;
                    if(lastAmount->next==nullptr) 
					{
                        lastAmount->next=idNode;
                        break;
                    }
                    curr=lastAmount->next;
                }
            }

            count++;
            cout<<"Expense added successfully!\n";
        }

        void viewAllExpenses()
        {
            if(count==0) 
			{
                cout<<"No expenses found.\n";
                return;
            }

            IdNode* curr=head;
            while(curr!=nullptr)
			{
                DateNode* date=curr->next;
                DetailNode* detail=date->next;
                AmountNode* amount=detail->next;

                cout<<"ID: "<<curr->id;
                cout<<", Date: "<<date->date;
                cout<<", Detail: "<<detail->detail;
                cout<<", Amount: "<<amount->amount<<endl;

                curr=amount->next;
            }
        }

        void editExpense()
        {
            if(count==0) 
			{
                cout<<"No expenses to edit.\n";
                return;
            }

            int editId;
            cout<<"Enter Expense ID to edit: ";
            cin>>editId;
            cin.ignore();

            IdNode* curr=head;
            while(curr!=nullptr&&curr->id!=editId) 
			{
                AmountNode* amount=curr->next->next->next;
                curr=amount->next;
            }
            if(curr==nullptr) 
			{
                cout<<"Expense with ID "<<editId<<" not found.\n";
                return;
            }
            DateNode* date=curr->next;
            DetailNode* detail=date->next;
            AmountNode* amount=detail->next;

            cout<<"Current Date: "<<date->date<<"\nEnter new Date (DD-MM-YYYY) or press Enter to keep current: ";
            string newDate;
            getline(cin, newDate);
            if(!newDate.empty()) 
			{
                date->date=newDate;
            }

            cout << "Current Detail: " << detail->detail << "\nEnter new Detail or press Enter to keep current: ";
            string newDetail;
            getline(cin, newDetail);
            if(!newDetail.empty()) 
			{
                detail->detail=newDetail;
            }

            cout<<"Current Amount: "<< amount->amount<<"\nEnter new Amount (or 0 to keep current): ";
            float newAmount;
            cin>>newAmount;
            cin.ignore();
            if(newAmount!=0)
			{
                amount->amount=newAmount;
            }
            cout<<"Expense updated successfully.\n";
        }
        void deleteExpense()
        {
            if (count==0)
			{
                cout<<"No expenses to delete.\n";
                return;
            }

            int delId;
            cout<<"Enter Expense ID to delete: ";
            cin>>delId;
            cin.ignore();
            
            IdNode* curr=head;
            IdNode* prev=nullptr;

            while(curr!=nullptr&&curr->id!=delId)
			{
                AmountNode* amount=curr->next->next->next;
                prev=curr;
                curr=amount->next;
            }

            if(curr==nullptr)
			{
                cout<<"Expense with ID "<<delId<<" not found.\n";
                return;
            }

            DateNode* date=curr->next;
            DetailNode* detail=date->next;
            AmountNode* amount=detail->next;

            if(prev==nullptr) 
			{
                head=amount->next;
            } 
			else 
			{
                AmountNode* prevAmount=prev->next->next->next;
                prevAmount->next=amount->next;
            }

            delete amount;
            delete detail;
            delete date;
            delete curr;

            count--;
            cout << "Expense deleted successfully.\n";
        }

        void generateReport()
        {
            if(count==0)
			{
                cout << "No expenses to report.\n";
                return;
            }
            float totalAmount=0;
            float highest=0.00;
            float lowest=0.00;
            int expenseCount=0;

            string recentDetail="";
            float recentAmount=0;
            IdNode* curr=head;
            while(curr!=nullptr)
			{
                DateNode* date=curr->next;
                DetailNode* detail=date->next;
                AmountNode* amount=detail->next;
                float amt=amount->amount;
                totalAmount+=amt;
                expenseCount++;

                if (amt>highest) highest=amt;
                if (amt<lowest) lowest=amt;

                recentDetail=detail->detail;
                recentAmount=amt;
                curr=amount->next;
            }

            cout<<"\n--- Expense Report ---\n";
            cout<<"Total expenses: "<<expenseCount<<endl;
            cout<<"Total amount spent: "<<totalAmount<<endl;
            cout<<"Highest expense: "<<highest<<endl;
            cout<<"Lowest expense: "<<lowest<<endl;
            cout<<"Most recent expense: "<<recentDetail<<" (Amount: "<<recentAmount<<")\n";
        }

        void menu()
        {
            int choice;
            do 
			{
                cout<<"\n--- Expense Tracker Menu ---\n";
                cout<<"1. Add Expense\n";
                cout<<"2. View All Expenses\n";
                cout<<"3. Edit Expense\n";
                cout<<"4. Delete Expense\n";
                cout<<"5. Generate Report\n";
                cout<<"0. Exit\n";
                cout<<"Enter your choice: ";
                cin>>choice;
                cin.ignore();

                switch(choice) 
				{
                    case 1:
                        addExpense();
                        break;
                    case 2:
                        viewAllExpenses();
                        break;
                    case 3:
                        editExpense();
                        break;
                    case 4:
                        deleteExpense();
                        break;
                    case 5:
                        generateReport();
                        break;
                    case 0:
                        cout << "Exiting...\n";
                        break;
                    default:
                        cout << "Invalid choice.\n";
                }
            } while(choice!=0);
        }
};

int main()
{
    ExpenseTracker tracker;
    tracker.menu();
    return 0;
}
