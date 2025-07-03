#include <iostream>
using namespace std;


enum enQuestionsLevel { EasyLevel =1, MedLevel, HardLevel, Mix};
enum enOperationType {Add=1, Sub, Mul, Div, MixOp};

struct stQuestion {
	int Number1 = 0;
	int Number2 = 0;
	enQuestionsLevel QuestionsLevel;
	enOperationType OperationType;
	int RightAnswer;
	int PlayerAnswer = 0;
	bool RightQuestions = false;
};

struct stQuizz {
	stQuestion Question[100];
	short ManyQuestions;
	enQuestionsLevel QuestionsLevel;
	enOperationType OperationType;
	int RightAnswers = 0;
	int WrongAnswer = 0;
};


/********************************************************************************/
// Section: User Inputs

short ReadHowManyQuestions()
{
	short NumberOfQuestions;
	do
	{
		cout << "How Many Questions do you want to answer? ";
		cin >> NumberOfQuestions;
	} while (NumberOfQuestions < 1 || NumberOfQuestions > 10);

	return NumberOfQuestions;
}

enQuestionsLevel ReadQuestionsLevel()
{
	short QuestionLevel;
	do
	{
		cout << "Enter Questions Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
		cin >> QuestionLevel;
	} while (QuestionLevel < 1 || QuestionLevel > 4);

	return (enQuestionsLevel)QuestionLevel;
}

enOperationType ReadOpType()
{
	short OpType;
	do
	{
		cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
		cin >> OpType;
	} while (OpType < 1 || OpType > 5);

	return (enOperationType)OpType;
}

int AnswerQestionUser() {
	int AnswerUser = 0;
	cin >> AnswerUser;
	return AnswerUser;
}

/*******************************/






/********************************************************************************/
// Section: Helper Functions

//									Random
int RandomNumber(int Min, int Max) {
	return rand() % (Max - Min + 1) + Min;
}

enOperationType GetRandomOpType() { // MixOp
	return (enOperationType)RandomNumber(1, 4);
}

enQuestionsLevel GetRandomQLevel() {
	return (enQuestionsLevel)RandomNumber(1, 5);
}


//									String
string GetQuestionLevelText(enQuestionsLevel QuestionsLevel) {
	string LevelText[] = { "EasyLevel", "MedLevel", "HardLevel", "Mix" };
	return LevelText[QuestionsLevel - 1];
}

string GetOpTypeSymbol(enOperationType OpType) {
	switch (OpType)
	{
	case Add: return "+";
	case Sub: return "-";
	case Mul: return "*";
	case Div: return "/";
	default:
		return "Mix";
		break;
	}
}


//									Screen
void ReasetSecrean() {
	system("cls");
	system("color 0F");
}

void  SetScreenColor(bool Right) {
	if (Right)
		system("color 2F"); // green
	else
	{
		system("color 4F"); // red
		cout << "\a";
	}
}


//									Calc
int SimpleCalc(int Number1, int Number2, enOperationType OperationType) {
	stQuestion Question;
	switch (OperationType)
	{
	case Add:  return Number1 + Number2;
	case Sub:  return Number1 - Number2;
	case Mul: return Number1 * Number2;
	case Div:  return (Number2 != 0) ? Number1 / Number2 : 0;
	default: return Number1 + Number2;
	}
}

/*******************************/







/********************************************************************************/

// Section: Game Logic

//									Check
stQuestion GenerateQuestion(enQuestionsLevel QuestionsLevel, enOperationType OperationType) {
	stQuestion Question;

	if (QuestionsLevel == enQuestionsLevel::Mix)
		QuestionsLevel = GetRandomQLevel();
	if (OperationType == enOperationType::MixOp)
		OperationType = GetRandomOpType();
	Question.OperationType = OperationType;

	switch (QuestionsLevel)
	{
	case EasyLevel:
		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);
		Question.RightAnswer = SimpleCalc(Question.Number1, Question.Number2, OperationType);
		Question.QuestionsLevel = QuestionsLevel;
		break;
	case enQuestionsLevel::MedLevel:
		Question.Number1 = RandomNumber(10, 50);
		Question.Number2 = RandomNumber(10, 50);
		Question.RightAnswer = SimpleCalc(Question.Number1, Question.Number2, OperationType);
		Question.QuestionsLevel = QuestionsLevel;
		break;
	case enQuestionsLevel::HardLevel:
		Question.Number1 = RandomNumber(50, 100);
		Question.Number2 = RandomNumber(50, 100);
		Question.RightAnswer = SimpleCalc(Question.Number1, Question.Number2, OperationType);
		Question.QuestionsLevel = QuestionsLevel;
		break;
	}
	return Question;
}

void CheckAnswer(stQuizz& Quizz, int Q) {
	if (Quizz.Question[Q].RightAnswer == Quizz.Question[Q].PlayerAnswer)
	{
		Quizz.Question[Q].RightQuestions = true;
		cout << "The Right Answer\n\n";
		Quizz.RightAnswers++;
	}
	else {
		cout << "The Wrong Answer\n\n";
		Quizz.WrongAnswer++;
	}


}

void FinalResult(stQuizz Quizz) {
	if (Quizz.RightAnswers > Quizz.WrongAnswer)
	{
		cout << " Final Result: PASS :-)";
	}
	else
	{
		cout << " Final Result : Fail";
	}
}


//									Print
void PrintQuestion(stQuizz& Quizz) {
	for (int Q = 0; Q < Quizz.ManyQuestions; Q++)
	{
		cout << "Question [" << Q + 1 << "/" << Quizz.ManyQuestions << "]\n";
		cout << Quizz.Question[Q].Number1 << " ";
		cout << GetOpTypeSymbol(Quizz.Question[Q].OperationType) << " ";
		cout << Quizz.Question[Q].Number2 << " = ";

		Quizz.Question[Q].PlayerAnswer = AnswerQestionUser();
		CheckAnswer(Quizz, Q);
		SetScreenColor(Quizz.Question[Q].RightQuestions);
		cout << "--------------------------------------------\n";
	}
}

void PrintResult(stQuizz& Quizz) {
	cout << "\n----------------------\n";
	FinalResult(Quizz);
	cout << "\n----------------------" << endl;;
	cout << "Number Of Questions: " << Quizz.ManyQuestions << endl;;
	cout << "Question Level: " << GetQuestionLevelText(Quizz.QuestionsLevel) << endl;;
	cout << "OpType: " << GetOpTypeSymbol(Quizz.OperationType) << endl;;
	cout << "Right Answers: " << Quizz.RightAnswers << endl;;
	cout << "Wrong Answers: " << Quizz.WrongAnswer << endl;;
	cout << "----------------------";

}


//									Run
void PlayMath(stQuizz& Quizz) {
	for (int Q = 0; Q < Quizz.ManyQuestions; Q++)
	{
		Quizz.Question[Q] = GenerateQuestion(Quizz.QuestionsLevel, Quizz.OperationType);
	}
}

void PlayGame() {
	stQuizz Quizz;

	Quizz.ManyQuestions = ReadHowManyQuestions();
	Quizz.QuestionsLevel = ReadQuestionsLevel();
	Quizz.OperationType = ReadOpType();

	PlayMath(Quizz);
	PrintQuestion(Quizz);
	PrintResult(Quizz);
}

void StartGame() {
	char PlayAgain = 'Y';
	do
	{
		ReasetSecrean();
		PlayGame();
		cout << "\nDo you want to play again? Y/N? ";
		cin >> PlayAgain;
	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

/*******************************/


int main(){
	srand((unsigned)time(NULL));
	StartGame();
}