#include <iostream>
#include <lib3mf_implicit.hpp>

int main() {
    try {
        std::cout << "Testing lib3mf integration..." << std::endl;
        
        // Create a new 3MF model
        auto pWrapper = Lib3MF::CWrapper::loadLibrary();
        auto pModel = pWrapper->CreateModel();
        
        std::cout << "lib3mf model created successfully!" << std::endl;
        std::cout << "Version: " << pWrapper->GetVersion() << std::endl;
        
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}