// -name:-Harshil Patel,
// - Seneca student ID:- 148847213,
// - Seneca email:- hpatel292@myseneca.ca
// - date of completion:- 04 April, 2023.
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.


#include<iostream>
#include "Workstation.h"
namespace sdds
{
	Workstation::Workstation(std::string& str) : sdds::Station(str)
	{
		m_pNextStation = nullptr;
	}
	void Workstation::fill(std::ostream& os)
	{
		if (!m_orders.empty()) {
			m_orders.front().fillItem(*this, os);
		}
	}
	bool Workstation::attemptToMoveOrder()
	{
		bool retValue = false;
		if (m_orders.size() != 0) {
			if (m_orders.front().isItemFilled(this->getItemName()) == true) {
				if (m_pNextStation == nullptr) {
					// move order to any of the global deques
					if (m_orders.front().isOrderFilled() == true) {
						g_completed.push_back(std::move(m_orders.front()));

					}
					else {
						g_incomplete.push_back(std::move(m_orders.front()));
					}
					m_orders.pop_front();
					retValue = true;
				}
				else {
					m_pNextStation->m_orders.push_back(std::move(m_orders.front()));
					m_orders.pop_front();
					retValue = true;
				}
			}
		}
		return retValue;
	}
	void Workstation::setNextStation(Workstation* station)
	{
		m_pNextStation = station;
	}
	Workstation* Workstation::getNextStation() const
	{
		return m_pNextStation;
	}
	void Workstation::display(std::ostream& os) const
	{
		os << this->getItemName();
		os << " --> ";
		if (m_pNextStation != nullptr) {
			os << m_pNextStation->getItemName() << std::endl;
		}
		else {
			os << "End of Line" << std::endl;
		}
	}
	Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
	{
		m_orders.push_back(std::move(newOrder));
		return *this;
	}
}