inline void pauser(){
    /// a portable way to pause a program
    std::string dummy;
    std::cout << "Press enter to continue...";
    std::getline(std::cin, dummy);
}

void FillMatrices(std::vector<std::vector<double>>& matBlock, std::mt19937_64& PRNG, std::uniform_real_distribution<double>& rngdist, const blasint randomMatSize, const uint32_t numConcurrentThreads){
	for(uint32_t i=0; i<3; i++){
		for(uint32_t j=0; j<(randomMatSize*randomMatSize); j++){
			matBlock[i][j] = rngdist(PRNG);
		}
	}
	for(uint32_t i=3; i<(numConcurrentThreads*3); i+=3){
			matBlock[i] = matBlock[0];
			matBlock[i+1] = matBlock[1];
			matBlock[i+2] = matBlock[2];
	}
}

std::mt19937_64 InitPRNG(){
	std::random_device rd;
	std::mt19937_64 PRNG(rd()); //seed PRNG using /dev/urandom or similar OS provided RNG
	std::uniform_real_distribution<double> rngdist{-1.0, 1.0};
	//make sure the internal state of the PRNG is properly mixed by generating 10M random numbers
	//PRNGs often have unreliable distribution uniformity and other statistical properties before their internal state is sufficiently mixed
	for (uint32_t i=0;i<10000000;i++) rngdist(PRNG);
	return PRNG;
}

void PrintMatrices(const std::vector<std::vector<double>>& matBlock, const blasint randomMatSize, const uint32_t numConcurrentThreads){
	for (uint32_t i=0;i<numConcurrentThreads*3;i++){
		std::cout<<i<<std::endl;
		for (uint32_t j=0;j<randomMatSize;j++){
			for (uint32_t k=0;k<randomMatSize;k++){
				std::cout<<matBlock[i][j*randomMatSize + k]<<"  ";
			}
			std::cout<<std::endl;
		}
		std::cout<<std::endl;
	}
}

