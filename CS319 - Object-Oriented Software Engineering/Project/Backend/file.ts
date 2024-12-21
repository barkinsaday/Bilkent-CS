export class file {
    //Properties
    content: number; //binary ?? (alternatively: use BinaryType)
    type: string;
    generatorId: number;

    //Constructors
    constructor(content: number = 0, type: string = "", generatorId: number = -1 ) {
        this.content = content;
        this.type = type;
        this.generatorId = generatorId;
    }

    //Methods
    setType(type: string): boolean {
        this.type = type;
        return true;
    }

    isEqual(f: file): boolean{
        if(this.content == f.content && this.type == f.type && this.generatorId == f.generatorId){
            return true;
        }
        return false;
    }

    //Not done
    getGeneratorId(): number {return this.generatorId;}

    loadBinary(): boolean{return false;};//low priority

    compressFile(): number {return this.content;}//low priority

    extractFile(): number {return this.content;}//low priority
}