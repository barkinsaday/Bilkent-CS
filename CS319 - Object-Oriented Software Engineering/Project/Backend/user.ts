import { email } from "./email";
import { equReq } from "./equReq";
import { file } from "./file";

export  class user {//TRY ABSTRACT: NO CONSTRUCTOR ?????
  //properties
  name: string;
  email: string;
  password: string;
  creationDate: string;
  isEmailConfirmed: boolean;
  id: number;
  emailList: email[];
  active: boolean;
  uploadedFiles: file[];

  constructor(
    name: string = "",
    email: string = "",
    password: string = "",
    creationDate: string = "",
    isEmailConfirmed: boolean = false,
    id: number = -1
  ) {
    this.name = name;
    this.email = email;
    this.creationDate = creationDate;
    this.password = password;
    this.isEmailConfirmed = isEmailConfirmed;
    this.id = id;
    this.emailList = [];
    this.active = false;
    this.uploadedFiles = [];
    //user.LoginPageHelper.addUser(this); //add the user instance to allUsers whenever a user is constructed
  }

    //Methods
    changePassword(password: string): boolean{
        this.password = password;
        return true;
    }

    changeUsername(userName: string): boolean{
        this.name = userName;
        return true;
    }

    sendEmail(u:user, title: string, cc: string, content: string): boolean{
        //Alternative instead of user get: username or cc ?
        let m = this.generateEmail(title, cc, content);
        return u.addEmail(m);
    }

    generateEmail(title: string, cc: string, content: string ): email{
        let mail: email = new email(this.id, title, cc, content);
        this.emailList.push(mail);
        return mail;
    }

    updateEmail(mailtoBeUpdated: string, cc: string, content: string ): boolean{
        for(let i=0; i<this.emailList.length ; i++){
            if(this.emailList[i].getTitle() == mailtoBeUpdated ){
                let mail = new email(this.id, mailtoBeUpdated, cc, content);
                this.emailList[i] = mail;//possible memory leak?
                return true;
            }    
        }
          return false;
    }

    addEmail(mail: email): boolean{//helper function
        this.emailList.push(mail);
        return true;
    }

    //Getter - Setter Methods
    public getName(): string {
        return this.name;
    }
    public setName(value: string) {
        this.name = value;
    }
    public getPassword(): string {
        return this.password;
    }
    public setPassword(value: string) {
        this.password = value;
    }
    public getCreationDate(): string {
        return this.creationDate;
    }
    public setCreationDate(value: string) {
        this.creationDate = value;
    }
    public getIsEmailConfirmed(): boolean {
        return this.isEmailConfirmed;
    }
    public setIsEmailConfirmed(value: boolean) {
        this.isEmailConfirmed = value;
    }
    public getId(): number {
        return this.id;
    }
    public setId(value: number) {
        this.id = value;
    }
    public getEmailList(): email[] {
        return this.emailList;
    }
    public setEmailList(value: email[]) {
        this.emailList = value;
    }
}//end of "user" class

//  =====================================================  STUDENT CLASS  =====================================================

class student extends user {
    //Properties
    approved: boolean;
    sentEquReqs: equReq[];

    //Constructors
    constructor(
        name: string,
        email: string,
        password: string,
        creationDate: string,
        isEmailConfirmed: boolean,
        id: number
      ) {
        super(name, email, password, creationDate, isEmailConfirmed, id); 
        //user.LoginPageHelper.addUser(this);//add the user instance to allUsers whenever a user is constructed
        this.approved = false;
        this.sentEquReqs = [];
    }

    //Methods
    downloadForm(f: file): boolean{
        //need UploadFilePageHelper
        this.uploadedFiles.push(f);// ?: uploadedFiles means files of the user ? 
        return true;//file check is not done
    }

    uploadForm(): boolean{
        //need UploadFilePageHelper
        //upload from uploadFiles to allFiles in global
        return true;//file check is not done
    }
    
    /*
    manipulateFile(): file{
        //need UploadFilePageHelper
        return null;
    }
    */

    generateEquReq(name: string, equivalent: string = ""): equReq{
        var req: equReq = new equReq(name, false, this.id, equivalent);
        return req;
    }

    sendEquReq(name: string, equivalent: string = ""): boolean{
        var req = this.generateEquReq(name, equivalent);
        if(req == null)
            return false;
        this.sentEquReqs.push(req);

        //tüm hocalara bu requesti ekle

        return true;
    }
}//end of "stundet" class

//  =====================================================  COORDINATOR CLASS  =====================================================

class coordinator extends user {
    //properties
    acceptedEquReqs: equReq[];
    pendingEquReqs: equReq[];
    approvedStudents: student[];
    
    //constructors
    constructor(
        name: string,
        email: string,
        password: string,
        creationDate: string,
        isEmailConfirmed: boolean,
        id: number
      ) {
        super(name, email, password, creationDate, isEmailConfirmed, id); 
            this.acceptedEquReqs = [];
            this.pendingEquReqs = [];
            this.approvedStudents = [];
            //user.LoginPageHelper.addUser(this);//add the user instance to allUsers whenever a user is constructed
        }

    //Methods
    downloadForm(): boolean{
        //need UploadFilePageHelper
        return true;
    }

    uploadForm(): boolean{
        //need UploadFilePageHelper
        return true;
    }
    
    /*
    manipulateFile(): file{
        //need UploadFilePageHelper
        return null;
    }
    */

    sendEquReqResponse(req: equReq, answer: boolean): boolean {//parameter: an equReq from pendingEquReqs
        //delete from pendingEquReqs for both answers
        let i = this.pendingEquReqs.indexOf(req);
            if(i>-1)
                this.pendingEquReqs.splice(i, 1);
            else
                return false;

        if(!answer)
            return false;

        //If response is yes: 
        req.approve();
        //remove from stundets sentEquReqs ???
        this.acceptedEquReqs.push(req);
        return true;
    }
}//end of "coordinator" class


//  =====================================================  INSTITUTION CLASS  =====================================================

class institution extends user{
    //properties
    createdCoordinators: coordinator[];
    createdStudents: student [];

    constructor(){//???
        super("BilkentInstitution", "erasmus@bilkent.edu.tr",
                "x2c3AA37fTW45", "xx/xx/xx", true, 1);//default values for the only institution account
        //user.LoginPageHelper.addUser(this);
    }

    createCoordinatorAccount(name: string, email: string, password: string, creationDate: string,
                            isEmailConfirmed: boolean, id: number): boolean{
        let account = new coordinator(name, email, password, creationDate, isEmailConfirmed, id);
        this.createdCoordinators.push(account);
        return true;//validation of name/password is not checked
    }

    createStudentAccount(name: string, email: string, password: string, creationDate: string,
                            isEmailConfirmed: boolean, id: number): boolean{
        let account = new student(name, email, password, creationDate, isEmailConfirmed, id);
        this.createdStudents.push(account);
        return true;//validation of name/password is not checked
    }

    deleteCoordinatorAccount(id: number): boolean{//delete by name / id?
        for(let i:number = 0; i<this.createdCoordinators.length; i++){
            if(this.createdCoordinators[i].getId() == id){
                this.createdCoordinators.splice(i, 1);
                return true;
            }
        }
        return false;//case: user not found
    }

    deleteStudentAccount(id: number): boolean{//delete by name / id?
        for(let i:number = 0; i<this.createdStudents.length; i++){
            if(this.createdStudents[i].getId() == id){
                this.createdStudents.splice(i, 1);
                return true;
            }
        }
        return false;//case: user not found
    }
}//end of "institution class"