#ifndef LINGO_H
#define LINGO_H

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace ProjectorRays {

enum IfType {
    kIf,
    kIfElse,
    kRepeatWhile
};

struct AST;
struct Bytecode;
struct CaseNode;
struct Node;
class ReadStream;
struct RepeatWithInStmtNode;
struct ScriptChunk;

typedef unsigned int uint;

enum OpCode {
    // single-byte
    kOpRet              = 0x01,
    kOpRetFactory       = 0x02,
    kOpPushZero         = 0x03,
    kOpMul              = 0x04,
    kOpAdd              = 0x05,
    kOpSub              = 0x06,
    kOpDiv              = 0x07,
    kOpMod              = 0x08,
    kOpInv              = 0x09,
    kOpJoinStr          = 0x0a,
    kOpJoinPadStr       = 0x0b,
    kOpLt               = 0x0c,
    kOpLtEq             = 0x0d,
    kOpNtEq             = 0x0e,
    kOpEq               = 0x0f,
    kOpGt               = 0x10,
    kOpGtEq             = 0x11,
    kOpAnd              = 0x12,
    kOpOr               = 0x13,
    kOpNot              = 0x14,
    kOpContainsStr      = 0x15,
    kOpContains0Str     = 0x16,
    kOpGetChunk         = 0x17,
    kOpHiliteChunk      = 0x18,
    kOpOntoSpr          = 0x19,
    kOpIntoSpr          = 0x1a,
    kOpGetField         = 0x1b,
    kOpStartObj         = 0x1c,
    kOpStopObj          = 0x1d,
    kOpPushList         = 0x1e,
    kOpPushPropList     = 0x1f,

    // multi-byte
    kOpPushInt8         = 0x41,
    kOpPushArgListNoRet = 0x42,
    kOpPushArgList      = 0x43,
    kOpPushCons         = 0x44,
    kOpPushSymb         = 0x45,
    kOpPushVarRef       = 0x46,
    kOpGetGlobal        = 0x49,
    kOpGetProp          = 0x4a,
    kOpGetParam         = 0x4b,
    kOpGetLocal         = 0x4c,
    kOpSetGlobal        = 0x4f,
    kOpSetProp          = 0x50,
    kOpSetParam         = 0x51,
    kOpSetLocal         = 0x52,
    kOpJmp              = 0x53,
    kOpEndRepeat        = 0x54,
    kOpJmpIfZ           = 0x55,
    kOpCallLocal        = 0x56,
    kOpCallExt          = 0x57,
    kOpCallObjOld       = 0x58,
    kOpPut              = 0x59,
    kOp5BXX             = 0x5b,
    kOpGet              = 0x5c,
    kOpSet              = 0x5d,
    kOpGetMovieProp     = 0x5f,
    kOpSetMovieProp     = 0x60,
    kOpGetObjProp       = 0x61,
    kOpSetObjProp       = 0x62,
    kOpPeek             = 0x64,
    kOpPop              = 0x65,
    kOpGetMovieInfo     = 0x66,
    kOpCallObj          = 0x67,
    kOpPushInt16        = 0x6e,
    kOpPushInt32        = 0x6f,
    kOpGetChainedProp   = 0x70,
    kOpPushFloat32      = 0x71,
    kOpGetTopLevelProp  = 0x72
};

enum DatumType {
    kDatumVoid,
    kDatumSymbol,
    kDatumVarRef,
    kDatumString,
    kDatumInt,
    kDatumFloat,
    kDatumList,
    kDatumArgList,
    kDatumArgListNoRet,
    kDatumPropList
};

enum ChunkType {
    kChunkChar  = 0x01,
    kChunkWord  = 0x02,
    kChunkItem  = 0x03,
    kChunkLine  = 0x04
};

enum PutType {
    kPutInto    = 0x01,
    kPutAfter   = 0x02,
    kPutBefore  = 0x03
};

enum NodeType {
    kNoneNode,
    kErrorNode,
    kTempNode,
    kCommentNode,
    kLiteralNode,
    kBlockNode,
    kHandlerNode,
    kExitStmtNode,
    kInverseOpNode,
    kNotOpNode,
    kBinaryOpNode,
    kChunkExprNode,
    kChunkHiliteStmtNode,
    kSpriteIntersectsExprNode,
    kSpriteWithinExprNode,
    kFieldExprNode,
    kMemberExprNode,
    kVarNode,
    kAssignmentStmtNode,
    kIfStmtNode,
    kRepeatWithInStmtNode,
    kCasesStmtNode,
    kCaseNode,
    kCallNode,
    kObjCallNode,
    kTheExprNode,
    kLastStringChunkExprNode,
    kStringChunkCountExprNode,
    kMenuPropExprNode,
    kMenuItemPropExprNode,
    kSoundPropExprNode,
    kSpritePropExprNode,
    kThePropExprNode,
    kObjPropExprNode,
    kObjBracketExprNode,
    kObjPropIndexExprNode,
    kExitRepeatStmtNode,
    kNextRepeatStmtNode,
    kPutStmtNode
};

enum CaseExpect {
    kCaseExpectPop,
    kCaseExpectOr,
    kCaseExpectNext,
    kCaseExpectOtherwise
};

/* Lingo */

struct Lingo {
    static std::map<uint, std::string> opcodeNames;
    static std::map<uint, std::string> binaryOpNames;
    static std::map<uint, std::string> moviePropertyNames00;
    static std::map<uint, std::string> timeNames;
    static std::map<uint, std::string> chunkTypeNames;
    static std::map<uint, std::string> putTypeNames;
    static std::map<uint, std::string> menuPropertyNames;
    static std::map<uint, std::string> menuItemPropertyNames;
    static std::map<uint, std::string> soundPropertyNames;
    static std::map<uint, std::string> spritePropertyNames;
    static std::map<uint, std::string> moviePropertyNames07;
    static std::map<uint, std::string> moviePropertyNames08;
    static std::map<uint, std::string> castPropertyNames09;
    static std::map<uint, std::string> fieldPropertyNames;
    static std::map<uint, std::string> castPropertyNames0D;

    static std::string getOpcodeName(uint8_t id);
    static std::string getName(const std::map<uint, std::string> &nameMap, uint id);
};

/* Datum */

struct Datum {
    DatumType type;
    int i;
    double f;
    std::string s;
    std::vector<std::shared_ptr<Node>> l;

    Datum() {
        type = kDatumVoid;
    }
    Datum(int val) {
        type = kDatumInt;
        i = val;
    }
    Datum(double val) {
        type = kDatumFloat;
        f = val;
    }
    Datum(DatumType t, std::string val) {
        type = t;
        s = val;
    }
    Datum(DatumType t, std::vector<std::shared_ptr<Node>> val) {
        type = t;
        l = val;
    }

    int toInt();
    std::string toString(bool dot, bool sum);
};

/* Handler */

struct Handler {
    int16_t nameID;
    uint16_t vectorPos;
    uint32_t compiledLen;
    uint32_t compiledOffset;
    uint16_t argumentCount;
    uint32_t argumentOffset;
    uint16_t localsCount;
    uint32_t localsOffset;
    uint16_t unknown0Count;
    uint32_t unknown0Offset;
    uint32_t unknown1;
    uint16_t unknown2;
    uint16_t lineCount;
    uint32_t lineOffset;
    uint32_t stackHeight;

    std::vector<int16_t> argumentNameIDs;
    std::vector<int16_t> localNameIDs;

    ScriptChunk *script;
    std::vector<Bytecode> bytecodeArray;
    std::map<uint32_t, size_t> bytecodePosMap;
    std::vector<std::string> argumentNames;
    std::vector<std::string> localNames;
    std::vector<std::string> globalNames;
    std::string name;

    std::vector<std::shared_ptr<Node>> stack;
    std::unique_ptr<AST> ast;

    Handler(ScriptChunk *s) {
        script = s;
    }

    void readRecord(ReadStream &stream);
    void readData(ReadStream &stream);
    std::vector<int16_t> readVarnamesTable(ReadStream &stream, uint16_t count, uint32_t offset);
    void readNames();
    std::string getName(int id);
    std::string getArgumentName(int id);
    std::string getLocalName(int id);
    std::string getGlobalName(int id);
    std::shared_ptr<Node> peek();
    std::shared_ptr<Node> pop();
    int variableMultiplier();
    void registerGlobal(const std::string &name);
    std::shared_ptr<Node> findVar(int varType, std::shared_ptr<Node> id, std::shared_ptr<Node> castID);
    std::shared_ptr<RepeatWithInStmtNode> buildRepeatWithIn(size_t index);
    void translate();
    size_t translateBytecode(Bytecode &bytecode, size_t pos);
    std::string bytecodeText();
};

/* Bytecode */

struct Bytecode {
    uint8_t opID;
    OpCode opcode;
    int32_t obj;
    int32_t pos;
    std::shared_ptr<Node> translation;

    Bytecode(uint8_t op, uint32_t o, int32_t p)
        : opID(op), obj(o), pos(p) {
        opcode = static_cast<OpCode>(op >= 0x40 ? 0x40 + op % 0x40 : op);
    }
};

/* Node */

struct Node {
    NodeType type;
    bool isExpression;
    bool isStatement;
    bool isLabel;
    Node *parent;

    Node(NodeType t) : type(t), isExpression(false), isStatement(false), isLabel(false), parent(nullptr) {}
    virtual ~Node() = default;
    virtual std::string toString(bool dot, bool sum);
    virtual std::shared_ptr<Datum> getValue();
    Node *ancestorStatement();
};

/* ExprNode */

struct ExprNode : Node {
    ExprNode(NodeType t) : Node(t) {
        isExpression = true;
    }
    virtual ~ExprNode() = default;
};

/* StmtNode */

struct StmtNode : Node {
    StmtNode(NodeType t) : Node(t) {
        isStatement = true;
    }
    virtual ~StmtNode() = default;
};

/* LabelNode */

struct LabelNode : Node {
    LabelNode(NodeType t) : Node(t) {
        isLabel = true;
    }
    virtual ~LabelNode() = default;
};

/* ErrorNode */

struct ErrorNode : ExprNode {
    ErrorNode() : ExprNode(kErrorNode) {}
    virtual ~ErrorNode() = default;
    virtual std::string toString(bool dot, bool sum);
};

/* TempNode */

struct TempNode : ExprNode {
    TempNode() : ExprNode(kTempNode) {}
    virtual ~TempNode() = default;
    virtual std::string toString(bool dot, bool sum);
};

/* CommentNode */

struct CommentNode : Node {
    std::string text;

    CommentNode(std::string t) : Node(kCommentNode), text(t) {}
    virtual ~CommentNode() = default;
    virtual std::string toString(bool dot, bool sum);
};

/* LiteralNode */

struct LiteralNode : ExprNode {
    std::shared_ptr<Datum> value;

    LiteralNode(std::shared_ptr<Datum> d) : ExprNode(kLiteralNode) {
        value = std::move(d);
    }
    virtual ~LiteralNode() = default;
    virtual std::string toString(bool dot, bool sum);
    virtual std::shared_ptr<Datum> getValue();
};

/* BlockNode */

struct BlockNode : ExprNode {
    std::vector<std::shared_ptr<Node>> children;

    // for use during translation:
    int32_t endPos;
    CaseNode *currentCase;

    BlockNode() : ExprNode(kBlockNode), endPos(-1), currentCase(nullptr) {}
    virtual ~BlockNode() = default;
    virtual std::string toString(bool dot, bool sum);
    void addChild(std::shared_ptr<Node> child);
};

/* HandlerNode */

struct HandlerNode : ExprNode {
    Handler *handler;
    std::shared_ptr<BlockNode> block;

    HandlerNode(Handler *h)
        : ExprNode(kHandlerNode), handler(h) {
        block = std::make_shared<BlockNode>();
        block->parent = this;
    }
    virtual ~HandlerNode() = default;
    virtual std::string toString(bool dot, bool sum);
};

/* ExitStmtNode */

struct ExitStmtNode : StmtNode {
    ExitStmtNode() : StmtNode(kExitStmtNode) {}
    virtual ~ExitStmtNode() = default;
    virtual std::string toString(bool dot, bool sum);
};

/* InverseOpNode */

struct InverseOpNode : ExprNode {
    std::shared_ptr<Node> operand;

    InverseOpNode(std::shared_ptr<Node> o) : ExprNode(kInverseOpNode) {
        operand = std::move(o);
        operand->parent = this;
    }
    virtual ~InverseOpNode() = default;
    virtual std::string toString(bool dot, bool sum);
};

/* NotOpNode */

struct NotOpNode : ExprNode {
    std::shared_ptr<Node> operand;

    NotOpNode(std::shared_ptr<Node> o) : ExprNode(kNotOpNode) {
        operand = std::move(o);
        operand->parent = this;
    }
    virtual ~NotOpNode() = default;
    virtual std::string toString(bool dot, bool sum);
};

/* BinaryOpNode */

struct BinaryOpNode : ExprNode {
    OpCode opcode;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;

    BinaryOpNode(OpCode op, std::shared_ptr<Node> a, std::shared_ptr<Node> b)
        : ExprNode(kBinaryOpNode), opcode(op) {
        left = std::move(a);
        left->parent = this;
        right = std::move(b);
        right->parent = this;
    }
    virtual ~BinaryOpNode() = default;
    virtual std::string toString(bool dot, bool sum);
};

/* ChunkExprNode */

struct ChunkExprNode : ExprNode {
    ChunkType type;
    std::shared_ptr<Node> first;
    std::shared_ptr<Node> last;
    std::shared_ptr<Node> string;

    ChunkExprNode(ChunkType t, std::shared_ptr<Node> a, std::shared_ptr<Node> b, std::shared_ptr<Node> s)
        : ExprNode(kChunkExprNode), type(t) {
        first = std::move(a);
        first->parent = this;
        last = std::move(b);
        last->parent = this;
        string = std::move(s);
        string->parent = this;
    }
    virtual ~ChunkExprNode() = default;
    virtual std::string toString(bool dot, bool sum);
};

/* ChunkHiliteStmtNode */

struct ChunkHiliteStmtNode : StmtNode {
    ChunkType type;
    std::shared_ptr<Node> first;
    std::shared_ptr<Node> last;
    std::shared_ptr<Node> field;

    ChunkHiliteStmtNode(ChunkType t, std::shared_ptr<Node> a, std::shared_ptr<Node> b, std::shared_ptr<Node> f)
        : StmtNode(kChunkHiliteStmtNode), type(t) {
        first = std::move(a);
        first->parent = this;
        last = std::move(b);
        last->parent = this;
        field = std::move(f);
        field->parent = this;
    }
    virtual ~ChunkHiliteStmtNode() = default;
    virtual std::string toString(bool dot, bool sum);
};

/* SpriteIntersectsExprNode */

struct SpriteIntersectsExprNode : ExprNode {
    std::shared_ptr<Node> firstSprite;
    std::shared_ptr<Node> secondSprite;

    SpriteIntersectsExprNode(std::shared_ptr<Node> a, std::shared_ptr<Node> b)
        : ExprNode(kSpriteIntersectsExprNode) {
        firstSprite = std::move(a);
        firstSprite->parent = this;
        secondSprite = std::move(b);
        secondSprite->parent = this;
    }
    virtual ~SpriteIntersectsExprNode() = default;
    virtual std::string toString(bool dot, bool sum);
};

/* SpriteWithinExprNode */

struct SpriteWithinExprNode : ExprNode {
    std::shared_ptr<Node> firstSprite;
    std::shared_ptr<Node> secondSprite;

    SpriteWithinExprNode(std::shared_ptr<Node> a, std::shared_ptr<Node> b)
        : ExprNode(kSpriteWithinExprNode) {
        firstSprite = std::move(a);
        firstSprite->parent = this;
        secondSprite = std::move(b);
        secondSprite->parent = this;
    }
    virtual ~SpriteWithinExprNode() = default;
    virtual std::string toString(bool dot, bool sum);
};

/* FieldExprNode */

struct FieldExprNode : ExprNode {
    std::shared_ptr<Node> fieldID;
    std::shared_ptr<Node> castID;

    FieldExprNode(std::shared_ptr<Node> fieldID, std::shared_ptr<Node> castID) : ExprNode(kFieldExprNode) {
        this->fieldID = std::move(fieldID);
        this->fieldID->parent = this;
        if (castID) {
            this->castID = std::move(castID);
            this->castID->parent = this;
        }
    }
    virtual ~FieldExprNode() = default;
    virtual std::string toString(bool dot, bool sum);
};

/* MemberExprNode */

struct MemberExprNode : ExprNode {
    std::shared_ptr<Node> memberID;
    std::shared_ptr<Node> castID;

    MemberExprNode(std::shared_ptr<Node> memberID, std::shared_ptr<Node> castID) : ExprNode(kMemberExprNode) {
        this->memberID = std::move(memberID);
        this->memberID->parent = this;
        if (castID) {
            this->castID = std::move(castID);
            this->castID->parent = this;
        }
    }
    virtual ~MemberExprNode() = default;
    virtual std::string toString(bool dot, bool sum);
};

/* VarNode */

struct VarNode : ExprNode {
    std::string varName;

    VarNode(std::string v) : ExprNode(kVarNode), varName(v) {}
    virtual ~VarNode() = default;
    virtual std::string toString(bool dot, bool sum);
};

/* AssignmentStmtNode */

struct AssignmentStmtNode : StmtNode {
    std::shared_ptr<Node> variable;
    std::shared_ptr<Node> value;

    AssignmentStmtNode(std::shared_ptr<Node> var, std::shared_ptr<Node> val)
        : StmtNode(kAssignmentStmtNode) {
        variable = std::move(var);
        variable->parent = this;
        value = std::move(val);
        value->parent = this;
    }

    virtual ~AssignmentStmtNode() = default;
    virtual std::string toString(bool dot, bool sum);
};

/* IfStmtNode */

struct IfStmtNode : StmtNode {
    IfType ifType;
    std::shared_ptr<Node> condition;
    std::shared_ptr<BlockNode> block1;
    std::shared_ptr<BlockNode> block2;

    IfStmtNode(std::shared_ptr<Node> c) : StmtNode(kIfStmtNode), ifType(kIf) {
        condition = std::move(c);
        condition->parent = this;
        block1 = std::make_shared<BlockNode>();
        block1->parent = this;
        block2 = std::make_shared<BlockNode>();
        block2->parent = this;
    }
    virtual ~IfStmtNode() = default;
    virtual std::string toString(bool dot, bool sum);
};

/* RepeatWithInStmtNode */

struct RepeatWithInStmtNode : StmtNode {
    std::string varName;
    std::shared_ptr<Node> list;
    std::shared_ptr<BlockNode> block;

    RepeatWithInStmtNode(std::string v) : StmtNode(kRepeatWithInStmtNode) {
        varName = v;
        block = std::make_shared<BlockNode>();
        block->parent = this;
    }
    virtual ~RepeatWithInStmtNode() = default;
    virtual std::string toString(bool dot, bool sum);
};

/* CaseNode */

struct CaseNode : LabelNode {
    std::shared_ptr<Node> value;
    CaseExpect expect;

    std::shared_ptr<CaseNode> nextOr;

    std::shared_ptr<CaseNode> nextCase;
    std::shared_ptr<BlockNode> block;
    std::shared_ptr<BlockNode> otherwise;

    CaseNode(std::shared_ptr<Node> v, CaseExpect e) : LabelNode(kCaseNode), expect(e) {
        value = std::move(v);
        value->parent = this;
    }
    virtual ~CaseNode() = default;
    virtual std::string toString(bool dot, bool sum);
};


/* CasesStmtNode */

struct CasesStmtNode : StmtNode {
    std::shared_ptr<Node> value;
    std::shared_ptr<CaseNode> firstCase;

    // for use during translation:
    int32_t endPos;

    CasesStmtNode(std::shared_ptr<Node> v) : StmtNode(kCasesStmtNode), endPos(-1) {
        value = std::move(v);
        value->parent = this;
    }
    virtual ~CasesStmtNode() = default;
    virtual std::string toString(bool dot, bool sum);
};

/* CallNode */

struct CallNode : Node {
    std::string name;
    std::shared_ptr<Node> argList;

    CallNode(std::string n, std::shared_ptr<Node> a) : Node(kCallNode) {
        name = n;
        argList = std::move(a);
        argList->parent = this;
        if (argList->getValue()->type == kDatumArgListNoRet)
            isStatement = true;
        else
            isExpression = true;
    }
    virtual ~CallNode() = default;
    bool noParens();
    virtual std::string toString(bool dot, bool sum);
};

/* ObjCallNode */

struct ObjCallNode : Node {
    std::string name;
    std::shared_ptr<Node> argList;

    ObjCallNode(std::string n, std::shared_ptr<Node> a) : Node(kObjCallNode) {
        name = n;
        argList = std::move(a);
        argList->parent = this;
        if (argList->getValue()->type == kDatumArgListNoRet)
            isStatement = true;
        else
            isExpression = true;
    }
    virtual ~ObjCallNode() = default;
    virtual std::string toString(bool dot, bool sum);
};

/* TheExprNode */

struct TheExprNode : ExprNode {
    std::string prop;

    TheExprNode(std::string p) : ExprNode(kTheExprNode), prop(p) {}
    virtual ~TheExprNode() = default;
    virtual std::string toString(bool dot, bool sum);
};

/* LastStringChunkExprNode */

struct LastStringChunkExprNode : ExprNode {
    ChunkType type;
    std::shared_ptr<Node> string;

    LastStringChunkExprNode(ChunkType t, std::shared_ptr<Node> s)
        : ExprNode(kLastStringChunkExprNode), type(t) {
        string = std::move(s);
        string->parent = this;
    }
    virtual ~LastStringChunkExprNode() = default;
    virtual std::string toString(bool dot, bool sum);
};

/* StringChunkCountExprNode */

struct StringChunkCountExprNode : ExprNode {
    ChunkType type;
    std::shared_ptr<Node> string;

    StringChunkCountExprNode(ChunkType t, std::shared_ptr<Node> s)
        : ExprNode(kStringChunkCountExprNode), type(t) {
        string = std::move(s);
        string->parent = this;
    }
    virtual ~StringChunkCountExprNode() = default;
    virtual std::string toString(bool dot, bool sum);
};

/* MenuPropExprNode */

struct MenuPropExprNode : ExprNode {
    std::shared_ptr<Node> menuID;
    uint prop;

    MenuPropExprNode(std::shared_ptr<Node> m, uint p)
        : ExprNode(kMenuPropExprNode), prop(p) {
        menuID = std::move(m);
        menuID->parent = this;
    }
    virtual ~MenuPropExprNode() = default;
    virtual std::string toString(bool dot, bool sum);
};

/* MenuItemPropExprNode */

struct MenuItemPropExprNode : ExprNode {
    std::shared_ptr<Node> menuID;
    std::shared_ptr<Node> itemID;
    uint prop;

    MenuItemPropExprNode(std::shared_ptr<Node> m, std::shared_ptr<Node> i, uint p)
        : ExprNode(kMenuItemPropExprNode), prop(p) {
        menuID = std::move(m);
        menuID->parent = this;
        itemID = std::move(i);
        itemID->parent = this;
    }
    virtual ~MenuItemPropExprNode() = default;
    virtual std::string toString(bool dot, bool sum);
};

/* SoundPropExprNode */

struct SoundPropExprNode : ExprNode {
    std::shared_ptr<Node> soundID;
    uint prop;

    SoundPropExprNode(std::shared_ptr<Node> s, uint p)
        : ExprNode(kSoundPropExprNode), prop(p) {
        soundID = std::move(s);
        soundID->parent = this;
    }
    virtual ~SoundPropExprNode() = default;
    virtual std::string toString(bool dot, bool sum);
};

/* SpritePropExprNode */

struct SpritePropExprNode : ExprNode {
    std::shared_ptr<Node> spriteID;
    uint prop;

    SpritePropExprNode(std::shared_ptr<Node> s, uint p)
        : ExprNode(kSpritePropExprNode), prop(p) {
        spriteID = std::move(s);
        spriteID->parent = this;
    }
    virtual ~SpritePropExprNode() = default;
    virtual std::string toString(bool dot, bool sum);
};

/* ThePropExprNode */

struct ThePropExprNode : ExprNode {
    std::shared_ptr<Node> obj;
    std::string prop;

    ThePropExprNode(std::shared_ptr<Node> o, std::string p)
        : ExprNode(kThePropExprNode), prop(p) {
        obj = std::move(o);
        obj->parent = this;
    }
    virtual ~ThePropExprNode() = default;
    virtual std::string toString(bool dot, bool sum);
};

/* ObjPropExprNode */

struct ObjPropExprNode : ExprNode {
    std::shared_ptr<Node> obj;
    std::string prop;

    ObjPropExprNode(std::shared_ptr<Node> o, std::string p)
        : ExprNode(kObjPropExprNode), prop(p) {
        obj = std::move(o);
        obj->parent = this;
    }
    virtual ~ObjPropExprNode() = default;
    virtual std::string toString(bool dot, bool sum);
};

/* ObjBracketExprNode */

struct ObjBracketExprNode : ExprNode {
    std::shared_ptr<Node> obj;
    std::shared_ptr<Node> prop;

    ObjBracketExprNode(std::shared_ptr<Node> o, std::shared_ptr<Node> p)
        : ExprNode(kObjBracketExprNode) {
        obj = std::move(o);
        obj->parent = this;
        prop = std::move(p);
        prop->parent = this;
    }
    virtual ~ObjBracketExprNode() = default;
    virtual std::string toString(bool dot, bool sum);
};

/* ObjPropIndexExprNode */

struct ObjPropIndexExprNode : ExprNode {
    std::shared_ptr<Node> obj;
    std::string prop;
    std::shared_ptr<Node> index;
    std::shared_ptr<Node> index2;

    ObjPropIndexExprNode(std::shared_ptr<Node> o, std::string p, std::shared_ptr<Node> i, std::shared_ptr<Node> i2)
        : ExprNode(kObjPropIndexExprNode), prop(p) {
        obj = std::move(o);
        obj->parent = this;
        index = std::move(i);
        index->parent = this;
        if (index2) {
            index2 = std::move(i2);
            index2->parent = this;
        }
    }
    virtual ~ObjPropIndexExprNode() = default;
    virtual std::string toString(bool dot, bool sum);
};

/* ExitRepeatStmtNode */

struct ExitRepeatStmtNode : StmtNode {
    ExitRepeatStmtNode() : StmtNode(kExitRepeatStmtNode) {}
    virtual ~ExitRepeatStmtNode() = default;
    virtual std::string toString(bool dot, bool sum);
};

/* NextRepeatStmtNode */

struct NextRepeatStmtNode : StmtNode {
    NextRepeatStmtNode() : StmtNode(kNextRepeatStmtNode) {}
    virtual ~NextRepeatStmtNode() = default;
    virtual std::string toString(bool dot, bool sum);
};

/* PutStmtNode */

struct PutStmtNode : StmtNode {
    PutType type;
    std::shared_ptr<Node> variable;
    std::shared_ptr<Node> value;

    PutStmtNode(PutType t, std::shared_ptr<Node> var, std::shared_ptr<Node> val)
        : StmtNode(kPutStmtNode), type(t) {
        variable = std::move(var);
        variable->parent = this;
        value = std::move(val);
        value->parent = this;
    }
    virtual ~PutStmtNode() = default;
    virtual std::string toString(bool dot, bool sum);
};

/* AST */

struct AST {
    std::shared_ptr<HandlerNode> root;
    BlockNode *currentBlock;

    AST(Handler *handler){
        root = std::make_shared<HandlerNode>(handler);
        currentBlock = root->block.get();
    }

    std::string toString(bool dot, bool sum);
    void addStatement(std::shared_ptr<Node> statement);
    void enterBlock(BlockNode *block);
    void exitBlock();
};

}

#endif
