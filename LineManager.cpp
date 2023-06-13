// -name:-Harshil Patel,
// - Seneca student ID:- 148847213,
// - Seneca email:- hpatel292@myseneca.ca
// - date of completion:- 04 April, 2023.
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.


#include<fstream>
#include<string>
#include<algorithm>
#include"Workstation.h"
#include "LineManager.h"
namespace sdds
{
	std::deque<sdds::CustomerOrder> g_pending;
	std::deque<sdds::CustomerOrder> g_completed;
	std::deque<sdds::CustomerOrder> g_incomplete;

	sdds::LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
	{
		std::vector<Workstation*> statPtr;
		std::string str; // holds whole line from file
		std::ifstream fileObj(file);
		while (fileObj) {
			std::string firstStation = "";
			std::string secondStation = "";
			std::getline(fileObj, str);
			if (fileObj) {
				int index = str.find("|");
				if (index == -1) {
					firstStation = str;
				}
				else {
					firstStation = str.substr(0, index);
					secondStation = str.substr(index + 1, str.length());
				}
				auto first = std::find_if(stations.begin(), stations.end(), [&](Workstation* station)->bool {
					return (station->getItemName() == firstStation) ? true : false;
					});
				if (secondStation != "") {

					auto second = std::find_if(stations.begin(), stations.end(), [&](Workstation* station)->bool {
						return (station->getItemName() == secondStation) ? true : false;
						});
					(*first)->setNextStation(*second);
					m_activeLine.push_back(*first);
					statPtr.push_back(*second);
				}
				else {
					(*first)->setNextStation(nullptr);
					m_activeLine.push_back(*first);
				}
			}
		}
		m_firstStation = nullptr;
		std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ptr){
			auto station = std::find_if(statPtr.begin(), statPtr.end(), [&](Workstation* ptr2) {
				return ptr2 == ptr;
				});
			if (station == statPtr.end()) {
				m_firstStation = ptr;
			}
		});
		if (m_firstStation == nullptr) {
			throw "Cannot able to find first station";
		}
		m_cntCustomerOrder = sdds::g_pending.size();
	}
	void LineManager::reorderStations()
	{
		
		std::vector<Workstation*> temp;
		temp.push_back(m_firstStation);
		while ((temp.back())->getNextStation() != nullptr) {
			Workstation* nextStation = temp.back()->getNextStation();
			auto station = std::find_if(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ptr) {
				return nextStation == ptr;
				});
			temp.push_back((*station));
		}
		if(temp.size() == m_activeLine.size())
			m_activeLine = temp;
	}
	bool LineManager::run(std::ostream& os)
	{
		bool retValue = false;
		os << "Line Manager Iteration: " << m_cnt++ << std::endl;
		if (g_pending.size() != 0) {
			(*m_firstStation) += std::move(g_pending.front());
			g_pending.pop_front();
		}
		for (size_t i = 0; i < m_activeLine.size(); i++)
		{
			m_activeLine[i]->fill(os);
			//m_activeLine[i]->attemptToMoveOrder();
		}
		for (size_t i = 0; i < m_activeLine.size(); i++)
		{
			//m_activeLine[i]->fill(os);
			m_activeLine[i]->attemptToMoveOrder();
		}

		if (g_completed.size() + g_incomplete.size() == m_cntCustomerOrder) {
			retValue = true;
		}
		return retValue;
	}
	void LineManager::display(std::ostream& os) const
	{
		for (size_t i = 0; i < m_activeLine.size(); i++)
		{
			m_activeLine[i]->display(os);
		}
	}
}