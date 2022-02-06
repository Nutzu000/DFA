#include "AFD.h"

AFD::AFD() :
	m_sigma{ "" },
	m_stareInitiala{ "" }
{
}

std::vector<std::string> AFD::getStari() const
{
	return m_stari;
}

std::string AFD::getSigma() const
{
	return m_sigma;
}

std::unordered_map<std::pair<std::string, std::string>, std::string, pair_hash> AFD::getDelta() const
{
	return m_delta;
}

std::string AFD::getStareInitiala() const
{
	return m_stareInitiala;
}

std::vector<std::string> AFD::getFinale() const
{
	return m_finale;
}

void AFD::setStari(std::vector<std::string> q)
{
	for (auto it : q) {
		m_stari.push_back(it);
	}
}

void AFD::setSigma(const std::string& sigma) {
	m_sigma = sigma;
}

void AFD::setDelta(std::unordered_map<std::pair<std::string, std::string>, std::string, pair_hash> delta)
{
	m_delta = delta;
}

void AFD::setStareInitiala(const std::string& q0)
{
	m_stareInitiala = q0;
}

void AFD::setFinale(std::vector<std::string> f)
{
	for (auto it : f) {
		m_finale.push_back(it);
	}
}

void AFD::citireFisier(const std::string& fisier)
{
	std::ifstream f(fisier);
	std::string aux;
	std::getline(f, aux);
	std::istringstream iss(aux);
	while (iss >> aux) {
		m_stari.push_back(aux);
	}
	std::getline(f, m_sigma);
	while (m_sigma.find(" ") != std::string::npos) {
		m_sigma.replace(m_sigma.find(" "), 1, "");
	}
	std::unordered_map<std::pair<std::string, std::string>, std::string, pair_hash> auxDelta;
	for (int i = 0; i < m_stari.size() * m_sigma.length(); i++) {
		std::getline(f, aux);
		std::istringstream iss(aux);
		std::string starePlecare, simbol, stareFinala;
		iss >> starePlecare >> simbol >> stareFinala;
		auxDelta[std::make_pair(starePlecare, simbol)] = stareFinala;
	}
	this->setDelta(auxDelta);
	f >> m_stareInitiala;
	std::getline(f, aux);
	std::getline(f, aux);
	std::istringstream iss2(aux);
	while (iss2 >> aux) {
		m_finale.push_back(aux);
	}

}

std::string AFD::accepta(const std::string& cuvant)
{
	std::string stareaCurenta = m_stareInitiala;
	for (auto& caracter:cuvant) {
		std::string simbol(1, caracter);
		stareaCurenta = m_delta[std::make_pair(stareaCurenta, simbol)];
		if (stareaCurenta == "vid") {
			return "BLOCAT";
		}
	}
	int esteFinala = 0;
	for (auto& it : m_finale) {
		if (it.find(stareaCurenta) != std::string::npos) {
			return "ACCEPTAT";
		}
	}
	return "NEACCEPTAT";
}

int AFD::verifica()
{
	int existaStareaInitiala = 0;
	for (int i = 0; i < m_stari.size() && !existaStareaInitiala; i++) {
		if (m_stari[i].find(m_stareInitiala) != std::string::npos) {
			existaStareaInitiala = 1;
		}
	}
	int existaUnFinal = 1, existaFinale = 1;
	for (int i = 0; i < m_finale.size() && existaUnFinal; i++) {
		existaFinale = 0;
		for (int j = 0; j < m_stari.size() && existaUnFinal; j++) {
			if (m_finale[i].find(m_stari[j]) != std::string::npos) {
				existaFinale = 1;
			}
		}
		if (existaFinale == 0) {
			existaUnFinal = 0;
		}
	}
	for (auto& it : m_delta) {
		int existaStare = 0;
		for (auto& stari : m_stari) {
			if (stari == it.first.first) {
				existaStare = 1;
			}
		}
		int existaSimbol = 0;
		if (m_sigma.find(it.first.second) != std::string::npos) {
			existaSimbol = 1;
		}

		int existaStari2 = 0;
		for (auto& stari : m_stari) {
			if (stari == it.second || "vid" == it.second) {
				existaStari2 = 1;
			}
		}
		if (!existaStare || !existaSimbol || !existaStari2) {
			return 0;
		}
	}
	return existaStareaInitiala && existaFinale;
}

std::ostream& operator<<(std::ostream& f, const AFD& afd)
{
	std::cout << "AFD={\n";

	for (auto it : afd.getStari()) {
		std::cout << it << ' ';
	}
	std::cout << "\nSigma:";
	for (auto it : afd.getSigma()) {
		std::cout << it << ' ';
	}
	std::cout << "\nDelta:\n";
	for (auto it : afd.getDelta()) {
		std::cout << it.first.first << ' ' << it.first.second << ' ' << it.second << ' ';
		std::cout << std::endl;
	}
	std::cout << "Starea initiala: " << afd.getStareInitiala()
		<< "\nStarile finale: ";
	for (auto it : afd.getFinale()) {
		std::cout << it << ' ';
	}
	std::cout << "\n}";
	return f;
}
