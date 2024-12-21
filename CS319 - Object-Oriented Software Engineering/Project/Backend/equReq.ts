export class equReq {
    //Properties
    className: string;
    approved: boolean;
    creatorId: number;
    whichClassToEquivalance: string;

    //Constructors
    constructor(name: string = "", approved: boolean = false, cID: number = -1, equivalent: string = "") {
        this.className = name;
        this.approved = approved;
        this.creatorId = cID;
        this. whichClassToEquivalance = equivalent;
    }

    //Methods
    approve(): void{this.approved = true;}

    deny(): void{this.approved = false;}
}