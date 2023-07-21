void fuzzyServo(){
    //fuzzy input 1
    FuzzyInput *inputPh = new FuzzyInput(1);
    inputPh->addFuzzySet(InputPhRendah);
    inputPh->addFuzzySet(InputPhTinggi);
    fuzzy->addFuzzyInput(inputPh);

    //fuzzy input 2
    FuzzyInput *inputKekeruhan = new FuzzyInput(2);
    inputKekeruhan->addFuzzySet(InputKekeruhanJernih);
    inputKekeruhan->addFuzzySet(InputKekeruhanKeruh);
    inputKekeruhan->addFuzzySet(InputKekeruhanSangatKeruh);
    fuzzy->addFuzzyInput(inputKekeruhan);

    //fuzzy output
    FuzzyOutput *outputServo = new FuzzyOutput(1);
    outputServo->addFuzzySet(ServoCepat);
    outputServo->addFuzzySet(ServoSedang);
    outputServo->addFuzzySet(ServoLama);
    fuzzy->addFuzzyOutput(outputServo);

    //Fuzzy Rules
    FuzzyRuleAntecedent *rule1 = new FuzzyRuleAntecedent();
    rule1->joinWithAND(InputPhRendah,InputKekeruhanJernih);
    FuzzyRuleConsequent *consequence1 = new FuzzyRuleConsequent();
    consequence1->addOutput(ServoSedang);
    FuzzyRule* FuzzyRule1 = new FuzzyRule(1,rule1,consequence1);
    fuzzy->addFuzzyRule(FuzzyRule1);

    FuzzyRuleAntecedent *rule2 = new FuzzyRuleAntecedent();
    rule2->joinWithAND(InputPhRendah,InputKekeruhanJernih);
    FuzzyRuleConsequent *consequence2 = new FuzzyRuleConsequent();
    consequence2->addOutput(ServoLama);
    FuzzyRule* FuzzyRule2 = new FuzzyRule(2,rule2,consequence2);
    fuzzy->addFuzzyRule(FuzzyRule2);

    FuzzyRuleAntecedent *rule3 = new FuzzyRuleAntecedent();
    rule3->joinWithAND(InputPhRendah,InputKekeruhanKeruh);
    FuzzyRuleConsequent *consequence3 = new FuzzyRuleConsequent();
    consequence3->addOutput(ServoCepat);
    FuzzyRule* FuzzyRule3 = new FuzzyRule(3,rule3,consequence3);
    fuzzy->addFuzzyRule(FuzzyRule3);

    FuzzyRuleAntecedent *rule4 = new FuzzyRuleAntecedent();
    rule4->joinWithAND(InputPhRendah,InputKekeruhanKeruh);
    FuzzyRuleConsequent *consequence4 = new FuzzyRuleConsequent();
    consequence4->addOutput(ServoSedang);
    FuzzyRule* FuzzyRule4 = new FuzzyRule(4,rule4,consequence4);
    fuzzy->addFuzzyRule(FuzzyRule4);

    FuzzyRuleAntecedent *rule5 = new FuzzyRuleAntecedent();
    rule5->joinWithAND(InputPhRendah,InputKekeruhanSangatKeruh);
    FuzzyRuleConsequent *consequence5 = new FuzzyRuleConsequent();
    consequence5->addOutput(ServoCepat);
    FuzzyRule* FuzzyRule5 = new FuzzyRule(5,rule5,consequence5);
    fuzzy->addFuzzyRule(FuzzyRule5);


    FuzzyRuleAntecedent *rule6 = new FuzzyRuleAntecedent();
    rule6->joinWithAND(InputPhTinggi,InputKekeruhanJernih);
    FuzzyRuleConsequent *consequence6 = new FuzzyRuleConsequent();
    consequence6->addOutput(ServoCepat);
    FuzzyRule* FuzzyRule6 = new FuzzyRule(6,rule6,consequence6);
    fuzzy->addFuzzyRule(FuzzyRule6);

    FuzzyRuleAntecedent *rule7 = new FuzzyRuleAntecedent();
    rule7->joinWithAND(InputPhTinggi,InputKekeruhanJernih);
    FuzzyRuleConsequent *consequence7 = new FuzzyRuleConsequent();
    consequence7->addOutput(ServoSedang);
    FuzzyRule* FuzzyRule7 = new FuzzyRule(7,rule7,consequence7);
    fuzzy->addFuzzyRule(FuzzyRule7);

    FuzzyRuleAntecedent *rule8 = new FuzzyRuleAntecedent();
    rule8->joinWithAND(InputPhTinggi,InputKekeruhanKeruh);
    FuzzyRuleConsequent *consequence8 = new FuzzyRuleConsequent();
    consequence8->addOutput(ServoCepat);
    FuzzyRule* FuzzyRule8 = new FuzzyRule(8,rule8,consequence8);
    fuzzy->addFuzzyRule(FuzzyRule8);

    FuzzyRuleAntecedent *rule9 = new FuzzyRuleAntecedent();
    rule9->joinWithAND(InputPhTinggi,InputKekeruhanKeruh);
    FuzzyRuleConsequent *consequence9 = new FuzzyRuleConsequent();
    consequence9->addOutput(ServoSedang);
    FuzzyRule* FuzzyRule9 = new FuzzyRule(9,rule9,consequence9);
    fuzzy->addFuzzyRule(FuzzyRule9);

    FuzzyRuleAntecedent *rule10 = new FuzzyRuleAntecedent();
    rule10->joinWithAND(InputPhTinggi,InputKekeruhanSangatKeruh);
    FuzzyRuleConsequent *consequence10 = new FuzzyRuleConsequent();
    consequence10->addOutput(ServoCepat);
    FuzzyRule* FuzzyRule10 = new FuzzyRule(10,rule10,consequence10);
    fuzzy->addFuzzyRule(FuzzyRule10);
}