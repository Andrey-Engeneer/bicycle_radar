#pragma once
namespace FlyingCircle {

	using namespace System;
	using namespace System::Threading;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: Thread^ myThread;
	private: System::Windows::Forms::Button^  startButton;
	private: System::Windows::Forms::PictureBox^  pictureBox;
	private: System::Windows::Forms::Button^  exitButton;


	private:
		/// <summary>
		/// Требуется переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Обязательный метод для поддержки конструктора - не изменяйте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->startButton = (gcnew System::Windows::Forms::Button());
			this->pictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->exitButton = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox))->BeginInit();
			this->SuspendLayout();
			// 
			// startButton
			// 
			this->startButton->Location = System::Drawing::Point(415, 27);
			this->startButton->Name = L"startButton";
			this->startButton->Size = System::Drawing::Size(75, 23);
			this->startButton->TabIndex = 0;
			this->startButton->Text = L"start";
			this->startButton->UseVisualStyleBackColor = true;
			this->startButton->Click += gcnew System::EventHandler(this, &MyForm::startButton_Click);
			// 
			// pictureBox
			// 
			this->pictureBox->Location = System::Drawing::Point(44, 107);
			this->pictureBox->Name = L"pictureBox";
			this->pictureBox->Size = System::Drawing::Size(263, 226);
			this->pictureBox->TabIndex = 1;
			this->pictureBox->TabStop = false;
			this->pictureBox->Click += gcnew System::EventHandler(this, &MyForm::pictureBox_Click);
			// 
			// exitButton
			// 
			this->exitButton->Location = System::Drawing::Point(559, 27);
			this->exitButton->Name = L"exitButton";
			this->exitButton->Size = System::Drawing::Size(75, 23);
			this->exitButton->TabIndex = 2;
			this->exitButton->Text = L"exit";
			this->exitButton->UseVisualStyleBackColor = true;
			this->exitButton->Click += gcnew System::EventHandler(this, &MyForm::exitButton_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(665, 481);
			this->Controls->Add(this->exitButton);
			this->Controls->Add(this->pictureBox);
			this->Controls->Add(this->startButton);
			this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"MyForm";
			this->Text = L"Круг";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MyForm::MyForm_FormClosing);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void startButton_Click(System::Object^  sender, System::EventArgs^  e) {
		// создаем и запускаем поток
		myThread = gcnew Thread(gcnew ThreadStart(this, &MyForm::Go));
		myThread->Start();
	}

	private: System::Void exitButton_Click(System::Object^  sender, System::EventArgs^  e) {
		// завершаем поток
		try {
			myThread->Abort();
		}
		catch (...) {}

		// закрываем форму
		this->Close();
	}

			 // данный метод будет исполняться в отдельном потоке
	public: void Go() {
		// делаем недоступной кнопку startButton
		startButton->BeginInvoke(gcnew InvokeDelegateStartButtonEnabled(this, &MyForm::SetStartButtonEnabled), false);

		// радиус круга
		int R = 30;

		// создаем изображение
		Bitmap^ image = gcnew Bitmap(pictureBox->Width, pictureBox->Height);

		// получаем объект для рисования
		Graphics^ g = Graphics::FromImage(image);

		// левый верхний -> правый верхний
		for (int x = 0; x <= pictureBox->Width - 2 * R; x += 2)
		{
			// заливка изображения белым цветом
			g->Clear(Color::White);

			// рисование окружности на изображении
			g->FillEllipse(Brushes::Aqua, x, 0, 2 * R, 2 * R);

			// вывод изображения в pictureBox
			pictureBox->BeginInvoke(gcnew InvokeDelegateImageToPictureBox(this, &MyForm::SetImageToPictureBox), image);

			// остановка потока на 10 мс
			Thread::Sleep(10);
		}

		// правый верхний -> правый нижний
		for (int y = 0; y <= pictureBox->Height - 2 * R; y += 2)
		{
			g->Clear(Color::White);

			g->FillEllipse(Brushes::Aqua, pictureBox->Width - 2 * R, y, 2 * R, 2 * R);

			pictureBox->BeginInvoke(gcnew InvokeDelegateImageToPictureBox(this, &MyForm::SetImageToPictureBox), image);

			Thread::Sleep(10);
		}

		// правый нижний -> левый нижний
		for (int x = pictureBox->Width - 2 * R; x >= 0; x -= 2)
		{
			g->Clear(Color::White);

			g->FillEllipse(Brushes::Aqua, x, pictureBox->Height - 2 * R, 2 * R, 2 * R);

			pictureBox->BeginInvoke(gcnew InvokeDelegateImageToPictureBox(this, &MyForm::SetImageToPictureBox), image);

			Thread::Sleep(10);
		}

		// левый нижний -> левый верхний
		for (int y = pictureBox->Height - 2 * R; y >= 0; y -= 2)
		{
			g->Clear(Color::White);

			g->FillEllipse(Brushes::Aqua, 0, y, 2 * R, 2 * R);

			pictureBox->BeginInvoke(gcnew InvokeDelegateImageToPictureBox(this, &MyForm::SetImageToPictureBox), image);

			Thread::Sleep(10);
		}

		// делаем доступной кнопку startButton
		startButton->BeginInvoke(gcnew InvokeDelegateStartButtonEnabled(this, &MyForm::SetStartButtonEnabled), true);
	}

			// делегат для вывода изображение в pictureBox
			delegate void InvokeDelegateImageToPictureBox(Bitmap^ image);

			// метод выводит изображение в pictureBox
	public: void SetImageToPictureBox(Bitmap^ image) {
		pictureBox->Image = image;
	}

			// делегат для изменения свойства Enabled у startButton
			delegate void InvokeDelegateStartButtonEnabled(bool enabled);

			// метод устанавливает свойство Enabled для startButton
	public: void SetStartButtonEnabled(bool enabled) {
		startButton->Enabled = enabled;
	}

	private: System::Void MyForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
		// завершаем поток
		try {
			myThread->Abort();
		}
		catch (...) {}
	}


	private: System::Void pictureBox_Click(System::Object^  sender, System::EventArgs^  e) {
	}

	
};
}