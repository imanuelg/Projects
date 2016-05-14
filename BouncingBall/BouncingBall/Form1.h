#pragma once

namespace BouncingBall {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	int ymove = 5;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  Start;
	private: System::Windows::Forms::PictureBox^  Ball;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::ComponentModel::IContainer^  components;
	protected: 


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->Start = (gcnew System::Windows::Forms::Button());
			this->Ball = (gcnew System::Windows::Forms::PictureBox());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->Ball))->BeginInit();
			this->SuspendLayout();
			// 
			// Start
			// 
			this->Start->Location = System::Drawing::Point(17, 18);
			this->Start->Name = L"Start";
			this->Start->Size = System::Drawing::Size(105, 50);
			this->Start->TabIndex = 0;
			this->Start->Text = L"Start";
			this->Start->UseVisualStyleBackColor = true;
			this->Start->Click += gcnew System::EventHandler(this, &Form1::Start_Click);
			// 
			// Ball
			// 
			this->Ball->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"Ball.Image")));
			this->Ball->Location = System::Drawing::Point(215, 19);
			this->Ball->Name = L"Ball";
			this->Ball->Size = System::Drawing::Size(132, 137);
			this->Ball->TabIndex = 1;
			this->Ball->TabStop = false;
			// 
			// timer1
			// 
			this->timer1->Interval = 5;
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Window;
			this->ClientSize = System::Drawing::Size(384, 761);
			this->Controls->Add(this->Ball);
			this->Controls->Add(this->Start);
			this->Name = L"Bouncing Ball";
			this->Text = L"Bouncing Ball";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->Ball))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Start_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->timer1->Start();
			 }
	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {

				 this->Ball->Top += ymove;

				 if (this->Ball->Top >= 630)
				 {
					 ymove = -ymove;
				 }

				 if (this->Ball->Top <= 0)
				 {
					 ymove = abs(ymove);
				 }
			 }
	};
}

