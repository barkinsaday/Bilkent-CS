import { file } from "./file";
import { user } from "./user";

export class email {
     //Properties
     private generatorId: number;
     private sendList: user[];
     private cc: string;
     private content: string;
     private attachments: file[];
     private title: string;
     
     //Constructors
    constructor(generatorId: number = -1, title: string = "", cc: string = "", content: string = "" ){ 
     this.title = title;
     this.generatorId = generatorId;
     this.cc = cc;
     this.content = content;
     this.attachments = [];
     this.sendList = [];
     }

    //Methods
     addAttachments(f: file): boolean {
          this.attachments.push(f);
          return true;
     }

     removeAttachments(f: file): boolean {
          let i = this.attachments.indexOf(f);
          if(i>-1){//item is found
               this.attachments.splice(i, 1);
               return true;
          }
          return false;
     }

     send(userToSend: user): boolean {
          return userToSend.addEmail(this);
     }

     addToSendList(u: user): boolean {
          let i = this.sendList.indexOf(u);
          if(i>-1){
               this.sendList.push(u);
               return true;
          }
          return false;
     }
     
     removeFromSendList(u: user): boolean {
          let i = this.sendList.indexOf(u);
          if(i>-1){
               this.sendList.splice(i, 1);
               return true;
          }
          return false;
     }
    
    //Getter - Setter Methods
    public getGeneratorId(): number {
     return this.generatorId;
     }
     public setGeneratorId(value: number) {
     this.generatorId = value;
     }
     public getSendList(): user[] {
          return this.sendList;
     }
     public setSendList(value: user[]) {
          this.sendList = value;
     }
     public getcc(): string {
          return this.cc;
     }
     public setcc(value: string) {
          this.cc = value;
     }
     public getContent(): string {
          return this.content;
     }
     public setContent(value: string) {
          this.content = value;
     }
     public getAttachments(): file[] {
          return this.attachments;
     }
     public setAttachments(value: file[]) {
          this.attachments = value;
     }
     public getTitle(): string {
          return this.title;
     }
     public setTitle(value: string) {
          this.title = value;
     }
}






