#include <iostream>
#include <cstdlib>

using namespace std;

enum enLevel { Easy = 1, Med = 2, Hard = 3, Mix = 4 };
enum enOperatorType { Add = 1, Sub = 2, Mul = 3, Div = 4, MixOp = 5 };

struct stQuestion {
	enLevel Level;
	enOperatorType Op;
	short Number1;
	short Number2;
	short Answer;
	short UserAnswer;
	bool Result;
};

struct stQueiz {
	stQuestion Question[100];
	enLevel Level;
	enOperatorType Op;
	short NumberOfQuestion;
	short NumberOfWrongAnswer =0;
	short NumberOfCorrectAnswer=0;
	bool FinalResult;
};

int RandomNumber(int From, int To) {
	return rand() % (To - From + 1) + From;
}

int SimpleCalculator(int n1, int n2, enOperatorType Op) {
	switch (Op)
	{
	case enOperatorType::Add:
		return n1 + n2;
		break;
	case enOperatorType::Sub:
		return n1 - n2;
		break;
	case enOperatorType::Mul:
		return n1 * n2;
		break;
	case enOperatorType::Div:
		return n1 / n2;
		break;
	default:
		return n1 + n2;
		break;
	}
}

enLevel ReadQuestionLeve() {
	int Level;
	do {
		cout << "Enter Question Level [1] Easy, Med[2] , Hard[3] , Mix[4]  ?";
		cin >> Level;
	} while (Level < 1 || Level>4);
	return (enLevel) Level;
}

enOperatorType ReadOperatorType() {
	int Op;
	do {
		cout << "Enter Operator Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ?";
		cin >> Op;
	} while (Op < 1 || Op>5);
	return (enOperatorType)Op;
}

void ResetScreen() {
	system("cls");
	system("color 0F");
}

void SetScreenAnswer(bool Answer) {
	if (Answer)
		system("color 2F");
	else
		system("color 4F");
}

stQuestion GenerateQuestion(enLevel Level, enOperatorType Op) {
	stQuestion Question;

	if (Level == enLevel::Mix)
		Level = (enLevel)RandomNumber(1, 3);

	Question.Level = Level;

	if (Op == enOperatorType::MixOp)
		Op = (enOperatorType)RandomNumber(1, 4);

	Question.Op = Op;


	switch (Level)
	{
	case enLevel::Easy:
		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);
		Question.Answer = SimpleCalculator(Question.Number1, Question.Number2, Question.Op);
		break;
	case enLevel::Med:
		Question.Number1 = RandomNumber(20, 50);
		Question.Number2 = RandomNumber(20, 50);
		Question.Answer = SimpleCalculator(Question.Number1, Question.Number2, Question.Op);
		break;
	case enLevel::Hard:
		Question.Number1 = RandomNumber(50, 100);
		Question.Number2 = RandomNumber(50, 100);
		Question.Answer = SimpleCalculator(Question.Number1, Question.Number2, Question.Op);
		break;
	default:
		break;
	}

	return Question;

}

string LevelName(enLevel Level) {
	string LevelName[] = { "Easy","Med","Hard"};
	return LevelName[Level - 1];
}

string OpName(enOperatorType Op) {
	string OpName[] = { "+","-","*","/"};
	return OpName[Op - 1];
}

string OpFullName(enOperatorType Op) {
	string OpName[] = { "Add","Sub","Mul","Div","Mix"};
	return OpName[Op - 1];
}

void PrintQuestion(stQuestion Question  ,short QuestionNumber,short TotalQuestion) {
	cout << "\n\nQuestion [" << QuestionNumber << "/" << TotalQuestion << "]\n\n";
	cout << Question.Number1 << endl;
	cout << Question.Number2 << " " << OpName(Question.Op) << "\n\n";
	cout << "__________________\n";
}

void GetUserAnswerAndCorrect(stQuestion &Question) {
	cin >> Question.UserAnswer;

	Question.Result = Question.Answer == Question.UserAnswer;

	if (Question.Result) {
		cout << "Right Answer :-)\n";
		SetScreenAnswer(Question.Result);
	}
	else {
		cout << "Wron Answer :-(\n";
		cout << "\a";
		cout << "The Right Answer is : " << Question.Answer << endl;
		SetScreenAnswer(Question.Result);
	}

		
}

int ReadHowManyQ() {
	int n;
	do {
		cout << "How Many Question YOu Wanna Do ? ";
		cin >> n;
	} while (n < 1 || n>10);
	return n;
}

void GeneraterQuestions(stQueiz &Quiz ,int NumberOfQuestion) {
	for (int QuestionN = 0; QuestionN < NumberOfQuestion; QuestionN++) {
		Quiz.Question[QuestionN] = GenerateQuestion(Quiz.Level, Quiz.Op);
	}
}

string ResultName(bool R) {
	if (R)
		return "Pass";
	return "Fail";
}

void PerintFinalResult(stQueiz Quiz) {
	cout << "\n\n_______________________\n\n";
	cout << "\n\nFinal Result is " << ResultName(Quiz.FinalResult) << endl;
	cout << "\n_______________________\n\n";
	cout << "Number Of Question : " << Quiz.NumberOfQuestion << endl;
	cout << "Question Level : " << LevelName(Quiz.Level) << endl;
	cout << "Op Type : " << OpFullName(Quiz.Op) << endl;
	cout << "Number Of Right Answer : " << Quiz.NumberOfCorrectAnswer << endl;
	cout << "Number Of Wrong Answer : " << Quiz.NumberOfWrongAnswer << endl;

	SetScreenAnswer(Quiz.FinalResult);
}

void PlayMathGame(short NumberOfQuestion) {
	stQueiz Quiz;
	Quiz.NumberOfQuestion = NumberOfQuestion;

	Quiz.Level = ReadQuestionLeve();
	Quiz.Op = ReadOperatorType();

	GeneraterQuestions(Quiz, NumberOfQuestion);

	for (int q = 0; q < NumberOfQuestion; q++) {

		PrintQuestion(Quiz.Question[q], q+1, NumberOfQuestion);
		
		GetUserAnswerAndCorrect(Quiz.Question[q]);

		if (Quiz.Question[q].Result)
			Quiz.NumberOfCorrectAnswer++;
		else
			Quiz.NumberOfWrongAnswer++;
	}

	if (Quiz.NumberOfCorrectAnswer < Quiz.NumberOfWrongAnswer)
		Quiz.FinalResult = false;
	else
		Quiz.FinalResult = true;

	PerintFinalResult(Quiz);
	
}

void StartGame() {
	char p = 'y';
	do {
		ResetScreen();
		PlayMathGame(ReadHowManyQ());
		cout << "Play Again? ";
		cin >> p;
	} while (p == 'y'||p=='Y');

}



int main() {
	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}
