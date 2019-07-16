#pragma once

namespace GUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Home
	/// </summary>
	public ref class Home : public System::Windows::Forms::Form
	{
	public:
		Home(void)
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
		~Home()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  asterixPosText;
	private: System::Windows::Forms::Button^  asterixPosSet;
	protected:

	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  asterixAltSet;

	private: System::Windows::Forms::TextBox^  asterixAltText;

	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Button^  obelixAltSet;

	private: System::Windows::Forms::TextBox^  obelixAltText;

	private: System::Windows::Forms::TextBox^  obelixPosText;
	private: System::Windows::Forms::Button^  obelixPosSet;


	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Button^  idefixAltSet;

	private: System::Windows::Forms::TextBox^  idefixAltText;


	private: System::Windows::Forms::TextBox^  idefixPosText;
	private: System::Windows::Forms::Button^  idefixPosSet;



	protected:

	protected:

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Home::typeid));
			this->asterixPosText = (gcnew System::Windows::Forms::TextBox());
			this->asterixPosSet = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->asterixAltText = (gcnew System::Windows::Forms::TextBox());
			this->asterixAltSet = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->obelixAltSet = (gcnew System::Windows::Forms::Button());
			this->obelixAltText = (gcnew System::Windows::Forms::TextBox());
			this->obelixPosText = (gcnew System::Windows::Forms::TextBox());
			this->obelixPosSet = (gcnew System::Windows::Forms::Button());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->idefixAltSet = (gcnew System::Windows::Forms::Button());
			this->idefixAltText = (gcnew System::Windows::Forms::TextBox());
			this->idefixPosText = (gcnew System::Windows::Forms::TextBox());
			this->idefixPosSet = (gcnew System::Windows::Forms::Button());
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->SuspendLayout();
			// 
			// asterixPosText
			// 
			this->asterixPosText->Location = System::Drawing::Point(56, 19);
			this->asterixPosText->Name = L"asterixPosText";
			this->asterixPosText->Size = System::Drawing::Size(117, 20);
			this->asterixPosText->TabIndex = 0;
			this->asterixPosText->TextChanged += gcnew System::EventHandler(this, &Home::asterixPosText_TextChanged);
			// 
			// asterixPosSet
			// 
			this->asterixPosSet->Location = System::Drawing::Point(179, 17);
			this->asterixPosSet->Name = L"asterixPosSet";
			this->asterixPosSet->Size = System::Drawing::Size(75, 23);
			this->asterixPosSet->TabIndex = 1;
			this->asterixPosSet->Text = L"Set";
			this->asterixPosSet->UseVisualStyleBackColor = true;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->asterixAltSet);
			this->groupBox1->Controls->Add(this->asterixAltText);
			this->groupBox1->Controls->Add(this->asterixPosText);
			this->groupBox1->Controls->Add(this->asterixPosSet);
			this->groupBox1->Location = System::Drawing::Point(12, 12);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(260, 73);
			this->groupBox1->TabIndex = 2;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Asterix";
			// 
			// asterixAltText
			// 
			this->asterixAltText->Location = System::Drawing::Point(56, 45);
			this->asterixAltText->Name = L"asterixAltText";
			this->asterixAltText->ReadOnly = true;
			this->asterixAltText->Size = System::Drawing::Size(117, 20);
			this->asterixAltText->TabIndex = 2;
			// 
			// asterixAltSet
			// 
			this->asterixAltSet->Enabled = false;
			this->asterixAltSet->Location = System::Drawing::Point(179, 43);
			this->asterixAltSet->Name = L"asterixAltSet";
			this->asterixAltSet->Size = System::Drawing::Size(75, 23);
			this->asterixAltSet->TabIndex = 3;
			this->asterixAltSet->Text = L"Set";
			this->asterixAltSet->UseVisualStyleBackColor = true;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(6, 22);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(44, 13);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Position";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(8, 48);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(42, 13);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Altitude";
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->label3);
			this->groupBox2->Controls->Add(this->label4);
			this->groupBox2->Controls->Add(this->obelixAltSet);
			this->groupBox2->Controls->Add(this->obelixAltText);
			this->groupBox2->Controls->Add(this->obelixPosText);
			this->groupBox2->Controls->Add(this->obelixPosSet);
			this->groupBox2->Location = System::Drawing::Point(12, 91);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(260, 73);
			this->groupBox2->TabIndex = 6;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Obelix";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(8, 48);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(42, 13);
			this->label3->TabIndex = 5;
			this->label3->Text = L"Altitude";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(6, 22);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(44, 13);
			this->label4->TabIndex = 4;
			this->label4->Text = L"Position";
			// 
			// obelixAltSet
			// 
			this->obelixAltSet->Enabled = false;
			this->obelixAltSet->Location = System::Drawing::Point(179, 43);
			this->obelixAltSet->Name = L"obelixAltSet";
			this->obelixAltSet->Size = System::Drawing::Size(75, 23);
			this->obelixAltSet->TabIndex = 3;
			this->obelixAltSet->Text = L"Set";
			this->obelixAltSet->UseVisualStyleBackColor = true;
			// 
			// obelixAltText
			// 
			this->obelixAltText->Location = System::Drawing::Point(56, 45);
			this->obelixAltText->Name = L"obelixAltText";
			this->obelixAltText->ReadOnly = true;
			this->obelixAltText->Size = System::Drawing::Size(117, 20);
			this->obelixAltText->TabIndex = 2;
			// 
			// obelixPosText
			// 
			this->obelixPosText->Location = System::Drawing::Point(56, 19);
			this->obelixPosText->Name = L"obelixPosText";
			this->obelixPosText->Size = System::Drawing::Size(117, 20);
			this->obelixPosText->TabIndex = 0;
			// 
			// obelixPosSet
			// 
			this->obelixPosSet->Location = System::Drawing::Point(179, 17);
			this->obelixPosSet->Name = L"obelixPosSet";
			this->obelixPosSet->Size = System::Drawing::Size(75, 23);
			this->obelixPosSet->TabIndex = 1;
			this->obelixPosSet->Text = L"Set";
			this->obelixPosSet->UseVisualStyleBackColor = true;
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->label5);
			this->groupBox3->Controls->Add(this->label6);
			this->groupBox3->Controls->Add(this->idefixAltSet);
			this->groupBox3->Controls->Add(this->idefixAltText);
			this->groupBox3->Controls->Add(this->idefixPosText);
			this->groupBox3->Controls->Add(this->idefixPosSet);
			this->groupBox3->Location = System::Drawing::Point(12, 176);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(260, 73);
			this->groupBox3->TabIndex = 6;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Idefix";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(8, 48);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(42, 13);
			this->label5->TabIndex = 5;
			this->label5->Text = L"Altitude";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(6, 22);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(44, 13);
			this->label6->TabIndex = 4;
			this->label6->Text = L"Position";
			// 
			// idefixAltSet
			// 
			this->idefixAltSet->Enabled = false;
			this->idefixAltSet->Location = System::Drawing::Point(179, 43);
			this->idefixAltSet->Name = L"idefixAltSet";
			this->idefixAltSet->Size = System::Drawing::Size(75, 23);
			this->idefixAltSet->TabIndex = 3;
			this->idefixAltSet->Text = L"Set";
			this->idefixAltSet->UseVisualStyleBackColor = true;
			// 
			// idefixAltText
			// 
			this->idefixAltText->Location = System::Drawing::Point(56, 45);
			this->idefixAltText->Name = L"idefixAltText";
			this->idefixAltText->ReadOnly = true;
			this->idefixAltText->Size = System::Drawing::Size(117, 20);
			this->idefixAltText->TabIndex = 2;
			// 
			// idefixPosText
			// 
			this->idefixPosText->Location = System::Drawing::Point(56, 19);
			this->idefixPosText->Name = L"idefixPosText";
			this->idefixPosText->Size = System::Drawing::Size(117, 20);
			this->idefixPosText->TabIndex = 0;
			// 
			// idefixPosSet
			// 
			this->idefixPosSet->Location = System::Drawing::Point(179, 17);
			this->idefixPosSet->Name = L"idefixPosSet";
			this->idefixPosSet->Size = System::Drawing::Size(75, 23);
			this->idefixPosSet->TabIndex = 1;
			this->idefixPosSet->Text = L"Set";
			this->idefixPosSet->UseVisualStyleBackColor = true;
			// 
			// Home
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"Home";
			this->Text = L"A&OXXL2 Hooker";
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->ResumeLayout(false);

			this->toggleMainUIElements();

		}
#pragma endregion
	private: 
		System::Void asterixPosText_TextChanged(System::Object^  sender, System::EventArgs^  e);

		void toggleMainUIElements();
};
}
