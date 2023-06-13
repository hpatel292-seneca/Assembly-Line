// -name:-Harshil Patel,
// - Seneca student ID:- 148847213,
// - Seneca email:- hpatel292@myseneca.ca
// - date of completion:- 04 April, 2023.
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.


#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H
#include<string>
#include<deque>
#include"CustomerOrder.h"
#include"Station.h"

namespace sdds
{
	extern std::deque<sdds::CustomerOrder> g_pending;
	extern std::deque<sdds::CustomerOrder> g_completed;
	extern std::deque<sdds::CustomerOrder> g_incomplete;
	class Workstation : public sdds::Station
	{
		std::deque<sdds::CustomerOrder> m_orders;
		Workstation* m_pNextStation;
	public:
		Workstation(const Workstation&) = delete;
		Workstation& operator=(const Workstation&) = delete;
		Workstation(Workstation&&) = delete;
		Workstation& operator=(Workstation&&) = delete;
		Workstation(std::string& str);
		void fill(std::ostream& os);
		bool attemptToMoveOrder();
		void setNextStation(Workstation* station);
		Workstation* getNextStation() const;
		void display(std::ostream& os) const;
		Workstation& operator+=(CustomerOrder&& newOrder);
	};
}
#endif
