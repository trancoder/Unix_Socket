struct MyStruct {
    int id;
    double value;
    std::string name;

    // Boost Serialization for the struct
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & id;
        ar & value;
        ar & name;
    }
};
