
// Generated from Solidity.g4 by ANTLR 4.7.2


#include "SolidityVisitor.h"

#include "SolidityParser.h"


using namespace antlrcpp;
using namespace antlr4;

SolidityParser::SolidityParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

SolidityParser::~SolidityParser() {
  delete _interpreter;
}

std::string SolidityParser::getGrammarFileName() const {
  return "Solidity.g4";
}

const std::vector<std::string>& SolidityParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& SolidityParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- SourceUnitContext ------------------------------------------------------------------

SolidityParser::SourceUnitContext::SourceUnitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SolidityParser::PragmaDirectiveContext *> SolidityParser::SourceUnitContext::pragmaDirective() {
  return getRuleContexts<SolidityParser::PragmaDirectiveContext>();
}

SolidityParser::PragmaDirectiveContext* SolidityParser::SourceUnitContext::pragmaDirective(size_t i) {
  return getRuleContext<SolidityParser::PragmaDirectiveContext>(i);
}

std::vector<SolidityParser::ImportDirectiveContext *> SolidityParser::SourceUnitContext::importDirective() {
  return getRuleContexts<SolidityParser::ImportDirectiveContext>();
}

SolidityParser::ImportDirectiveContext* SolidityParser::SourceUnitContext::importDirective(size_t i) {
  return getRuleContext<SolidityParser::ImportDirectiveContext>(i);
}

std::vector<SolidityParser::ContractDefinitionContext *> SolidityParser::SourceUnitContext::contractDefinition() {
  return getRuleContexts<SolidityParser::ContractDefinitionContext>();
}

SolidityParser::ContractDefinitionContext* SolidityParser::SourceUnitContext::contractDefinition(size_t i) {
  return getRuleContext<SolidityParser::ContractDefinitionContext>(i);
}


size_t SolidityParser::SourceUnitContext::getRuleIndex() const {
  return SolidityParser::RuleSourceUnit;
}


antlrcpp::Any SolidityParser::SourceUnitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitSourceUnit(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::SourceUnitContext* SolidityParser::sourceUnit() {
  SourceUnitContext *_localctx = _tracker.createInstance<SourceUnitContext>(_ctx, getState());
  enterRule(_localctx, 0, SolidityParser::RuleSourceUnit);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(173);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SolidityParser::T__0)
      | (1ULL << SolidityParser::T__10)
      | (1ULL << SolidityParser::T__16)
      | (1ULL << SolidityParser::T__17)
      | (1ULL << SolidityParser::T__18))) != 0)) {
      setState(171);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case SolidityParser::T__0: {
          setState(168);
          pragmaDirective();
          break;
        }

        case SolidityParser::T__10: {
          setState(169);
          importDirective();
          break;
        }

        case SolidityParser::T__16:
        case SolidityParser::T__17:
        case SolidityParser::T__18: {
          setState(170);
          contractDefinition();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(175);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PragmaDirectiveContext ------------------------------------------------------------------

SolidityParser::PragmaDirectiveContext::PragmaDirectiveContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SolidityParser::PragmaNameContext* SolidityParser::PragmaDirectiveContext::pragmaName() {
  return getRuleContext<SolidityParser::PragmaNameContext>(0);
}

SolidityParser::PragmaValueContext* SolidityParser::PragmaDirectiveContext::pragmaValue() {
  return getRuleContext<SolidityParser::PragmaValueContext>(0);
}


size_t SolidityParser::PragmaDirectiveContext::getRuleIndex() const {
  return SolidityParser::RulePragmaDirective;
}


antlrcpp::Any SolidityParser::PragmaDirectiveContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitPragmaDirective(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::PragmaDirectiveContext* SolidityParser::pragmaDirective() {
  PragmaDirectiveContext *_localctx = _tracker.createInstance<PragmaDirectiveContext>(_ctx, getState());
  enterRule(_localctx, 2, SolidityParser::RulePragmaDirective);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(176);
    match(SolidityParser::T__0);
    setState(177);
    pragmaName();
    setState(178);
    pragmaValue();
    setState(179);
    match(SolidityParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PragmaNameContext ------------------------------------------------------------------

SolidityParser::PragmaNameContext::PragmaNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SolidityParser::IdentifierContext* SolidityParser::PragmaNameContext::identifier() {
  return getRuleContext<SolidityParser::IdentifierContext>(0);
}


size_t SolidityParser::PragmaNameContext::getRuleIndex() const {
  return SolidityParser::RulePragmaName;
}


antlrcpp::Any SolidityParser::PragmaNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitPragmaName(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::PragmaNameContext* SolidityParser::pragmaName() {
  PragmaNameContext *_localctx = _tracker.createInstance<PragmaNameContext>(_ctx, getState());
  enterRule(_localctx, 4, SolidityParser::RulePragmaName);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(181);
    identifier();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PragmaValueContext ------------------------------------------------------------------

SolidityParser::PragmaValueContext::PragmaValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SolidityParser::VersionContext* SolidityParser::PragmaValueContext::version() {
  return getRuleContext<SolidityParser::VersionContext>(0);
}

SolidityParser::ExpressionContext* SolidityParser::PragmaValueContext::expression() {
  return getRuleContext<SolidityParser::ExpressionContext>(0);
}


size_t SolidityParser::PragmaValueContext::getRuleIndex() const {
  return SolidityParser::RulePragmaValue;
}


antlrcpp::Any SolidityParser::PragmaValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitPragmaValue(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::PragmaValueContext* SolidityParser::pragmaValue() {
  PragmaValueContext *_localctx = _tracker.createInstance<PragmaValueContext>(_ctx, getState());
  enterRule(_localctx, 6, SolidityParser::RulePragmaValue);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(185);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(183);
      version();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(184);
      expression(0);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VersionContext ------------------------------------------------------------------

SolidityParser::VersionContext::VersionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SolidityParser::VersionConstraintContext *> SolidityParser::VersionContext::versionConstraint() {
  return getRuleContexts<SolidityParser::VersionConstraintContext>();
}

SolidityParser::VersionConstraintContext* SolidityParser::VersionContext::versionConstraint(size_t i) {
  return getRuleContext<SolidityParser::VersionConstraintContext>(i);
}


size_t SolidityParser::VersionContext::getRuleIndex() const {
  return SolidityParser::RuleVersion;
}


antlrcpp::Any SolidityParser::VersionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitVersion(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::VersionContext* SolidityParser::version() {
  VersionContext *_localctx = _tracker.createInstance<VersionContext>(_ctx, getState());
  enterRule(_localctx, 8, SolidityParser::RuleVersion);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(187);
    versionConstraint();
    setState(189);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SolidityParser::T__2)
      | (1ULL << SolidityParser::T__3)
      | (1ULL << SolidityParser::T__4)
      | (1ULL << SolidityParser::T__5)
      | (1ULL << SolidityParser::T__6)
      | (1ULL << SolidityParser::T__7)
      | (1ULL << SolidityParser::T__8))) != 0) || _la == SolidityParser::VersionLiteral) {
      setState(188);
      versionConstraint();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VersionOperatorContext ------------------------------------------------------------------

SolidityParser::VersionOperatorContext::VersionOperatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SolidityParser::VersionOperatorContext::getRuleIndex() const {
  return SolidityParser::RuleVersionOperator;
}


antlrcpp::Any SolidityParser::VersionOperatorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitVersionOperator(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::VersionOperatorContext* SolidityParser::versionOperator() {
  VersionOperatorContext *_localctx = _tracker.createInstance<VersionOperatorContext>(_ctx, getState());
  enterRule(_localctx, 10, SolidityParser::RuleVersionOperator);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(191);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SolidityParser::T__2)
      | (1ULL << SolidityParser::T__3)
      | (1ULL << SolidityParser::T__4)
      | (1ULL << SolidityParser::T__5)
      | (1ULL << SolidityParser::T__6)
      | (1ULL << SolidityParser::T__7)
      | (1ULL << SolidityParser::T__8))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VersionConstraintContext ------------------------------------------------------------------

SolidityParser::VersionConstraintContext::VersionConstraintContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SolidityParser::VersionConstraintContext::VersionLiteral() {
  return getToken(SolidityParser::VersionLiteral, 0);
}

SolidityParser::VersionOperatorContext* SolidityParser::VersionConstraintContext::versionOperator() {
  return getRuleContext<SolidityParser::VersionOperatorContext>(0);
}


size_t SolidityParser::VersionConstraintContext::getRuleIndex() const {
  return SolidityParser::RuleVersionConstraint;
}


antlrcpp::Any SolidityParser::VersionConstraintContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitVersionConstraint(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::VersionConstraintContext* SolidityParser::versionConstraint() {
  VersionConstraintContext *_localctx = _tracker.createInstance<VersionConstraintContext>(_ctx, getState());
  enterRule(_localctx, 12, SolidityParser::RuleVersionConstraint);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(194);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SolidityParser::T__2)
      | (1ULL << SolidityParser::T__3)
      | (1ULL << SolidityParser::T__4)
      | (1ULL << SolidityParser::T__5)
      | (1ULL << SolidityParser::T__6)
      | (1ULL << SolidityParser::T__7)
      | (1ULL << SolidityParser::T__8))) != 0)) {
      setState(193);
      versionOperator();
    }
    setState(196);
    match(SolidityParser::VersionLiteral);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ImportDeclarationContext ------------------------------------------------------------------

SolidityParser::ImportDeclarationContext::ImportDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SolidityParser::IdentifierContext *> SolidityParser::ImportDeclarationContext::identifier() {
  return getRuleContexts<SolidityParser::IdentifierContext>();
}

SolidityParser::IdentifierContext* SolidityParser::ImportDeclarationContext::identifier(size_t i) {
  return getRuleContext<SolidityParser::IdentifierContext>(i);
}


size_t SolidityParser::ImportDeclarationContext::getRuleIndex() const {
  return SolidityParser::RuleImportDeclaration;
}


antlrcpp::Any SolidityParser::ImportDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitImportDeclaration(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::ImportDeclarationContext* SolidityParser::importDeclaration() {
  ImportDeclarationContext *_localctx = _tracker.createInstance<ImportDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 14, SolidityParser::RuleImportDeclaration);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(198);
    identifier();
    setState(201);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SolidityParser::T__9) {
      setState(199);
      match(SolidityParser::T__9);
      setState(200);
      identifier();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ImportDirectiveContext ------------------------------------------------------------------

SolidityParser::ImportDirectiveContext::ImportDirectiveContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SolidityParser::ImportDirectiveContext::StringLiteral() {
  return getToken(SolidityParser::StringLiteral, 0);
}

std::vector<SolidityParser::IdentifierContext *> SolidityParser::ImportDirectiveContext::identifier() {
  return getRuleContexts<SolidityParser::IdentifierContext>();
}

SolidityParser::IdentifierContext* SolidityParser::ImportDirectiveContext::identifier(size_t i) {
  return getRuleContext<SolidityParser::IdentifierContext>(i);
}

std::vector<SolidityParser::ImportDeclarationContext *> SolidityParser::ImportDirectiveContext::importDeclaration() {
  return getRuleContexts<SolidityParser::ImportDeclarationContext>();
}

SolidityParser::ImportDeclarationContext* SolidityParser::ImportDirectiveContext::importDeclaration(size_t i) {
  return getRuleContext<SolidityParser::ImportDeclarationContext>(i);
}


size_t SolidityParser::ImportDirectiveContext::getRuleIndex() const {
  return SolidityParser::RuleImportDirective;
}


antlrcpp::Any SolidityParser::ImportDirectiveContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitImportDirective(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::ImportDirectiveContext* SolidityParser::importDirective() {
  ImportDirectiveContext *_localctx = _tracker.createInstance<ImportDirectiveContext>(_ctx, getState());
  enterRule(_localctx, 16, SolidityParser::RuleImportDirective);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(237);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(203);
      match(SolidityParser::T__10);
      setState(204);
      match(SolidityParser::StringLiteral);
      setState(207);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == SolidityParser::T__9) {
        setState(205);
        match(SolidityParser::T__9);
        setState(206);
        identifier();
      }
      setState(209);
      match(SolidityParser::T__1);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(210);
      match(SolidityParser::T__10);
      setState(213);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case SolidityParser::T__11: {
          setState(211);
          match(SolidityParser::T__11);
          break;
        }

        case SolidityParser::T__12:
        case SolidityParser::T__39:
        case SolidityParser::Identifier: {
          setState(212);
          identifier();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(217);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == SolidityParser::T__9) {
        setState(215);
        match(SolidityParser::T__9);
        setState(216);
        identifier();
      }
      setState(219);
      match(SolidityParser::T__12);
      setState(220);
      match(SolidityParser::StringLiteral);
      setState(221);
      match(SolidityParser::T__1);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(222);
      match(SolidityParser::T__10);
      setState(223);
      match(SolidityParser::T__13);
      setState(224);
      importDeclaration();
      setState(229);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == SolidityParser::T__14) {
        setState(225);
        match(SolidityParser::T__14);
        setState(226);
        importDeclaration();
        setState(231);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(232);
      match(SolidityParser::T__15);
      setState(233);
      match(SolidityParser::T__12);
      setState(234);
      match(SolidityParser::StringLiteral);
      setState(235);
      match(SolidityParser::T__1);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ContractDefinitionContext ------------------------------------------------------------------

SolidityParser::ContractDefinitionContext::ContractDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SolidityParser::IdentifierContext* SolidityParser::ContractDefinitionContext::identifier() {
  return getRuleContext<SolidityParser::IdentifierContext>(0);
}

std::vector<SolidityParser::InheritanceSpecifierContext *> SolidityParser::ContractDefinitionContext::inheritanceSpecifier() {
  return getRuleContexts<SolidityParser::InheritanceSpecifierContext>();
}

SolidityParser::InheritanceSpecifierContext* SolidityParser::ContractDefinitionContext::inheritanceSpecifier(size_t i) {
  return getRuleContext<SolidityParser::InheritanceSpecifierContext>(i);
}

std::vector<SolidityParser::ContractPartContext *> SolidityParser::ContractDefinitionContext::contractPart() {
  return getRuleContexts<SolidityParser::ContractPartContext>();
}

SolidityParser::ContractPartContext* SolidityParser::ContractDefinitionContext::contractPart(size_t i) {
  return getRuleContext<SolidityParser::ContractPartContext>(i);
}


size_t SolidityParser::ContractDefinitionContext::getRuleIndex() const {
  return SolidityParser::RuleContractDefinition;
}


antlrcpp::Any SolidityParser::ContractDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitContractDefinition(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::ContractDefinitionContext* SolidityParser::contractDefinition() {
  ContractDefinitionContext *_localctx = _tracker.createInstance<ContractDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 18, SolidityParser::RuleContractDefinition);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(239);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SolidityParser::T__16)
      | (1ULL << SolidityParser::T__17)
      | (1ULL << SolidityParser::T__18))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(240);
    identifier();
    setState(250);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SolidityParser::T__19) {
      setState(241);
      match(SolidityParser::T__19);
      setState(242);
      inheritanceSpecifier();
      setState(247);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == SolidityParser::T__14) {
        setState(243);
        match(SolidityParser::T__14);
        setState(244);
        inheritanceSpecifier();
        setState(249);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(252);
    match(SolidityParser::T__13);
    setState(256);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SolidityParser::T__12)
      | (1ULL << SolidityParser::T__22)
      | (1ULL << SolidityParser::T__24)
      | (1ULL << SolidityParser::T__25)
      | (1ULL << SolidityParser::T__26)
      | (1ULL << SolidityParser::T__27)
      | (1ULL << SolidityParser::T__29)
      | (1ULL << SolidityParser::T__30)
      | (1ULL << SolidityParser::T__33)
      | (1ULL << SolidityParser::T__35)
      | (1ULL << SolidityParser::T__39)
      | (1ULL << SolidityParser::T__48)
      | (1ULL << SolidityParser::T__49)
      | (1ULL << SolidityParser::T__50)
      | (1ULL << SolidityParser::T__51))) != 0) || ((((_la - 91) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 91)) & ((1ULL << (SolidityParser::Int - 91))
      | (1ULL << (SolidityParser::Uint - 91))
      | (1ULL << (SolidityParser::Byte - 91))
      | (1ULL << (SolidityParser::Fixed - 91))
      | (1ULL << (SolidityParser::Ufixed - 91))
      | (1ULL << (SolidityParser::Identifier - 91)))) != 0)) {
      setState(253);
      contractPart();
      setState(258);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(259);
    match(SolidityParser::T__15);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InheritanceSpecifierContext ------------------------------------------------------------------

SolidityParser::InheritanceSpecifierContext::InheritanceSpecifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SolidityParser::UserDefinedTypeNameContext* SolidityParser::InheritanceSpecifierContext::userDefinedTypeName() {
  return getRuleContext<SolidityParser::UserDefinedTypeNameContext>(0);
}

std::vector<SolidityParser::ExpressionContext *> SolidityParser::InheritanceSpecifierContext::expression() {
  return getRuleContexts<SolidityParser::ExpressionContext>();
}

SolidityParser::ExpressionContext* SolidityParser::InheritanceSpecifierContext::expression(size_t i) {
  return getRuleContext<SolidityParser::ExpressionContext>(i);
}


size_t SolidityParser::InheritanceSpecifierContext::getRuleIndex() const {
  return SolidityParser::RuleInheritanceSpecifier;
}


antlrcpp::Any SolidityParser::InheritanceSpecifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitInheritanceSpecifier(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::InheritanceSpecifierContext* SolidityParser::inheritanceSpecifier() {
  InheritanceSpecifierContext *_localctx = _tracker.createInstance<InheritanceSpecifierContext>(_ctx, getState());
  enterRule(_localctx, 20, SolidityParser::RuleInheritanceSpecifier);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(261);
    userDefinedTypeName();
    setState(273);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SolidityParser::T__20) {
      setState(262);
      match(SolidityParser::T__20);
      setState(263);
      expression(0);
      setState(268);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == SolidityParser::T__14) {
        setState(264);
        match(SolidityParser::T__14);
        setState(265);
        expression(0);
        setState(270);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(271);
      match(SolidityParser::T__21);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ContractPartContext ------------------------------------------------------------------

SolidityParser::ContractPartContext::ContractPartContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SolidityParser::StateVariableDeclarationContext* SolidityParser::ContractPartContext::stateVariableDeclaration() {
  return getRuleContext<SolidityParser::StateVariableDeclarationContext>(0);
}

SolidityParser::UsingForDeclarationContext* SolidityParser::ContractPartContext::usingForDeclaration() {
  return getRuleContext<SolidityParser::UsingForDeclarationContext>(0);
}

SolidityParser::StructDefinitionContext* SolidityParser::ContractPartContext::structDefinition() {
  return getRuleContext<SolidityParser::StructDefinitionContext>(0);
}

SolidityParser::ConstructorDefinitionContext* SolidityParser::ContractPartContext::constructorDefinition() {
  return getRuleContext<SolidityParser::ConstructorDefinitionContext>(0);
}

SolidityParser::ModifierDefinitionContext* SolidityParser::ContractPartContext::modifierDefinition() {
  return getRuleContext<SolidityParser::ModifierDefinitionContext>(0);
}

SolidityParser::FunctionDefinitionContext* SolidityParser::ContractPartContext::functionDefinition() {
  return getRuleContext<SolidityParser::FunctionDefinitionContext>(0);
}

SolidityParser::EventDefinitionContext* SolidityParser::ContractPartContext::eventDefinition() {
  return getRuleContext<SolidityParser::EventDefinitionContext>(0);
}

SolidityParser::EnumDefinitionContext* SolidityParser::ContractPartContext::enumDefinition() {
  return getRuleContext<SolidityParser::EnumDefinitionContext>(0);
}


size_t SolidityParser::ContractPartContext::getRuleIndex() const {
  return SolidityParser::RuleContractPart;
}


antlrcpp::Any SolidityParser::ContractPartContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitContractPart(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::ContractPartContext* SolidityParser::contractPart() {
  ContractPartContext *_localctx = _tracker.createInstance<ContractPartContext>(_ctx, getState());
  enterRule(_localctx, 22, SolidityParser::RuleContractPart);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(283);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(275);
      stateVariableDeclaration();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(276);
      usingForDeclaration();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(277);
      structDefinition();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(278);
      constructorDefinition();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(279);
      modifierDefinition();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(280);
      functionDefinition();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(281);
      eventDefinition();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(282);
      enumDefinition();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StateVariableDeclarationContext ------------------------------------------------------------------

SolidityParser::StateVariableDeclarationContext::StateVariableDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SolidityParser::TypeNameContext* SolidityParser::StateVariableDeclarationContext::typeName() {
  return getRuleContext<SolidityParser::TypeNameContext>(0);
}

SolidityParser::IdentifierContext* SolidityParser::StateVariableDeclarationContext::identifier() {
  return getRuleContext<SolidityParser::IdentifierContext>(0);
}

SolidityParser::ExpressionContext* SolidityParser::StateVariableDeclarationContext::expression() {
  return getRuleContext<SolidityParser::ExpressionContext>(0);
}

std::vector<tree::TerminalNode *> SolidityParser::StateVariableDeclarationContext::PublicKeyword() {
  return getTokens(SolidityParser::PublicKeyword);
}

tree::TerminalNode* SolidityParser::StateVariableDeclarationContext::PublicKeyword(size_t i) {
  return getToken(SolidityParser::PublicKeyword, i);
}

std::vector<tree::TerminalNode *> SolidityParser::StateVariableDeclarationContext::InternalKeyword() {
  return getTokens(SolidityParser::InternalKeyword);
}

tree::TerminalNode* SolidityParser::StateVariableDeclarationContext::InternalKeyword(size_t i) {
  return getToken(SolidityParser::InternalKeyword, i);
}

std::vector<tree::TerminalNode *> SolidityParser::StateVariableDeclarationContext::PrivateKeyword() {
  return getTokens(SolidityParser::PrivateKeyword);
}

tree::TerminalNode* SolidityParser::StateVariableDeclarationContext::PrivateKeyword(size_t i) {
  return getToken(SolidityParser::PrivateKeyword, i);
}

std::vector<tree::TerminalNode *> SolidityParser::StateVariableDeclarationContext::ConstantKeyword() {
  return getTokens(SolidityParser::ConstantKeyword);
}

tree::TerminalNode* SolidityParser::StateVariableDeclarationContext::ConstantKeyword(size_t i) {
  return getToken(SolidityParser::ConstantKeyword, i);
}


size_t SolidityParser::StateVariableDeclarationContext::getRuleIndex() const {
  return SolidityParser::RuleStateVariableDeclaration;
}


antlrcpp::Any SolidityParser::StateVariableDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitStateVariableDeclaration(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::StateVariableDeclarationContext* SolidityParser::stateVariableDeclaration() {
  StateVariableDeclarationContext *_localctx = _tracker.createInstance<StateVariableDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 24, SolidityParser::RuleStateVariableDeclaration);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(285);
    typeName(0);
    setState(289);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((((_la - 105) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 105)) & ((1ULL << (SolidityParser::ConstantKeyword - 105))
      | (1ULL << (SolidityParser::InternalKeyword - 105))
      | (1ULL << (SolidityParser::PrivateKeyword - 105))
      | (1ULL << (SolidityParser::PublicKeyword - 105)))) != 0)) {
      setState(286);
      _la = _input->LA(1);
      if (!(((((_la - 105) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 105)) & ((1ULL << (SolidityParser::ConstantKeyword - 105))
        | (1ULL << (SolidityParser::InternalKeyword - 105))
        | (1ULL << (SolidityParser::PrivateKeyword - 105))
        | (1ULL << (SolidityParser::PublicKeyword - 105)))) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(291);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(292);
    identifier();
    setState(295);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SolidityParser::T__8) {
      setState(293);
      match(SolidityParser::T__8);
      setState(294);
      expression(0);
    }
    setState(297);
    match(SolidityParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UsingForDeclarationContext ------------------------------------------------------------------

SolidityParser::UsingForDeclarationContext::UsingForDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SolidityParser::IdentifierContext* SolidityParser::UsingForDeclarationContext::identifier() {
  return getRuleContext<SolidityParser::IdentifierContext>(0);
}

SolidityParser::TypeNameContext* SolidityParser::UsingForDeclarationContext::typeName() {
  return getRuleContext<SolidityParser::TypeNameContext>(0);
}


size_t SolidityParser::UsingForDeclarationContext::getRuleIndex() const {
  return SolidityParser::RuleUsingForDeclaration;
}


antlrcpp::Any SolidityParser::UsingForDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitUsingForDeclaration(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::UsingForDeclarationContext* SolidityParser::usingForDeclaration() {
  UsingForDeclarationContext *_localctx = _tracker.createInstance<UsingForDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 26, SolidityParser::RuleUsingForDeclaration);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(299);
    match(SolidityParser::T__22);
    setState(300);
    identifier();
    setState(301);
    match(SolidityParser::T__23);
    setState(304);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SolidityParser::T__11: {
        setState(302);
        match(SolidityParser::T__11);
        break;
      }

      case SolidityParser::T__12:
      case SolidityParser::T__27:
      case SolidityParser::T__33:
      case SolidityParser::T__35:
      case SolidityParser::T__39:
      case SolidityParser::T__48:
      case SolidityParser::T__49:
      case SolidityParser::T__50:
      case SolidityParser::T__51:
      case SolidityParser::Int:
      case SolidityParser::Uint:
      case SolidityParser::Byte:
      case SolidityParser::Fixed:
      case SolidityParser::Ufixed:
      case SolidityParser::Identifier: {
        setState(303);
        typeName(0);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(306);
    match(SolidityParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StructDefinitionContext ------------------------------------------------------------------

SolidityParser::StructDefinitionContext::StructDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SolidityParser::IdentifierContext* SolidityParser::StructDefinitionContext::identifier() {
  return getRuleContext<SolidityParser::IdentifierContext>(0);
}

std::vector<SolidityParser::VariableDeclarationContext *> SolidityParser::StructDefinitionContext::variableDeclaration() {
  return getRuleContexts<SolidityParser::VariableDeclarationContext>();
}

SolidityParser::VariableDeclarationContext* SolidityParser::StructDefinitionContext::variableDeclaration(size_t i) {
  return getRuleContext<SolidityParser::VariableDeclarationContext>(i);
}


size_t SolidityParser::StructDefinitionContext::getRuleIndex() const {
  return SolidityParser::RuleStructDefinition;
}


antlrcpp::Any SolidityParser::StructDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitStructDefinition(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::StructDefinitionContext* SolidityParser::structDefinition() {
  StructDefinitionContext *_localctx = _tracker.createInstance<StructDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 28, SolidityParser::RuleStructDefinition);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(308);
    match(SolidityParser::T__24);
    setState(309);
    identifier();
    setState(310);
    match(SolidityParser::T__13);
    setState(321);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SolidityParser::T__12)
      | (1ULL << SolidityParser::T__27)
      | (1ULL << SolidityParser::T__33)
      | (1ULL << SolidityParser::T__35)
      | (1ULL << SolidityParser::T__39)
      | (1ULL << SolidityParser::T__48)
      | (1ULL << SolidityParser::T__49)
      | (1ULL << SolidityParser::T__50)
      | (1ULL << SolidityParser::T__51))) != 0) || ((((_la - 91) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 91)) & ((1ULL << (SolidityParser::Int - 91))
      | (1ULL << (SolidityParser::Uint - 91))
      | (1ULL << (SolidityParser::Byte - 91))
      | (1ULL << (SolidityParser::Fixed - 91))
      | (1ULL << (SolidityParser::Ufixed - 91))
      | (1ULL << (SolidityParser::Identifier - 91)))) != 0)) {
      setState(311);
      variableDeclaration();
      setState(312);
      match(SolidityParser::T__1);
      setState(318);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << SolidityParser::T__12)
        | (1ULL << SolidityParser::T__27)
        | (1ULL << SolidityParser::T__33)
        | (1ULL << SolidityParser::T__35)
        | (1ULL << SolidityParser::T__39)
        | (1ULL << SolidityParser::T__48)
        | (1ULL << SolidityParser::T__49)
        | (1ULL << SolidityParser::T__50)
        | (1ULL << SolidityParser::T__51))) != 0) || ((((_la - 91) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 91)) & ((1ULL << (SolidityParser::Int - 91))
        | (1ULL << (SolidityParser::Uint - 91))
        | (1ULL << (SolidityParser::Byte - 91))
        | (1ULL << (SolidityParser::Fixed - 91))
        | (1ULL << (SolidityParser::Ufixed - 91))
        | (1ULL << (SolidityParser::Identifier - 91)))) != 0)) {
        setState(313);
        variableDeclaration();
        setState(314);
        match(SolidityParser::T__1);
        setState(320);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(323);
    match(SolidityParser::T__15);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstructorDefinitionContext ------------------------------------------------------------------

SolidityParser::ConstructorDefinitionContext::ConstructorDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SolidityParser::ParameterListContext* SolidityParser::ConstructorDefinitionContext::parameterList() {
  return getRuleContext<SolidityParser::ParameterListContext>(0);
}

SolidityParser::ModifierListContext* SolidityParser::ConstructorDefinitionContext::modifierList() {
  return getRuleContext<SolidityParser::ModifierListContext>(0);
}

SolidityParser::BlockContext* SolidityParser::ConstructorDefinitionContext::block() {
  return getRuleContext<SolidityParser::BlockContext>(0);
}


size_t SolidityParser::ConstructorDefinitionContext::getRuleIndex() const {
  return SolidityParser::RuleConstructorDefinition;
}


antlrcpp::Any SolidityParser::ConstructorDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitConstructorDefinition(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::ConstructorDefinitionContext* SolidityParser::constructorDefinition() {
  ConstructorDefinitionContext *_localctx = _tracker.createInstance<ConstructorDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 30, SolidityParser::RuleConstructorDefinition);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(325);
    match(SolidityParser::T__25);
    setState(326);
    parameterList();
    setState(327);
    modifierList();
    setState(328);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ModifierDefinitionContext ------------------------------------------------------------------

SolidityParser::ModifierDefinitionContext::ModifierDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SolidityParser::IdentifierContext* SolidityParser::ModifierDefinitionContext::identifier() {
  return getRuleContext<SolidityParser::IdentifierContext>(0);
}

SolidityParser::BlockContext* SolidityParser::ModifierDefinitionContext::block() {
  return getRuleContext<SolidityParser::BlockContext>(0);
}

SolidityParser::ParameterListContext* SolidityParser::ModifierDefinitionContext::parameterList() {
  return getRuleContext<SolidityParser::ParameterListContext>(0);
}


size_t SolidityParser::ModifierDefinitionContext::getRuleIndex() const {
  return SolidityParser::RuleModifierDefinition;
}


antlrcpp::Any SolidityParser::ModifierDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitModifierDefinition(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::ModifierDefinitionContext* SolidityParser::modifierDefinition() {
  ModifierDefinitionContext *_localctx = _tracker.createInstance<ModifierDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 32, SolidityParser::RuleModifierDefinition);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(330);
    match(SolidityParser::T__26);
    setState(331);
    identifier();
    setState(333);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SolidityParser::T__20) {
      setState(332);
      parameterList();
    }
    setState(335);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ModifierInvocationContext ------------------------------------------------------------------

SolidityParser::ModifierInvocationContext::ModifierInvocationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SolidityParser::IdentifierContext* SolidityParser::ModifierInvocationContext::identifier() {
  return getRuleContext<SolidityParser::IdentifierContext>(0);
}

SolidityParser::ExpressionListContext* SolidityParser::ModifierInvocationContext::expressionList() {
  return getRuleContext<SolidityParser::ExpressionListContext>(0);
}


size_t SolidityParser::ModifierInvocationContext::getRuleIndex() const {
  return SolidityParser::RuleModifierInvocation;
}


antlrcpp::Any SolidityParser::ModifierInvocationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitModifierInvocation(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::ModifierInvocationContext* SolidityParser::modifierInvocation() {
  ModifierInvocationContext *_localctx = _tracker.createInstance<ModifierInvocationContext>(_ctx, getState());
  enterRule(_localctx, 34, SolidityParser::RuleModifierInvocation);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(337);
    identifier();
    setState(343);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SolidityParser::T__20) {
      setState(338);
      match(SolidityParser::T__20);
      setState(340);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << SolidityParser::T__3)
        | (1ULL << SolidityParser::T__12)
        | (1ULL << SolidityParser::T__20)
        | (1ULL << SolidityParser::T__31)
        | (1ULL << SolidityParser::T__33)
        | (1ULL << SolidityParser::T__39)
        | (1ULL << SolidityParser::T__48)
        | (1ULL << SolidityParser::T__49)
        | (1ULL << SolidityParser::T__50)
        | (1ULL << SolidityParser::T__51)
        | (1ULL << SolidityParser::T__52)
        | (1ULL << SolidityParser::T__53)
        | (1ULL << SolidityParser::T__54)
        | (1ULL << SolidityParser::T__55)
        | (1ULL << SolidityParser::T__56)
        | (1ULL << SolidityParser::T__57)
        | (1ULL << SolidityParser::T__58)
        | (1ULL << SolidityParser::T__59))) != 0) || ((((_la - 91) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 91)) & ((1ULL << (SolidityParser::Int - 91))
        | (1ULL << (SolidityParser::Uint - 91))
        | (1ULL << (SolidityParser::Byte - 91))
        | (1ULL << (SolidityParser::Fixed - 91))
        | (1ULL << (SolidityParser::Ufixed - 91))
        | (1ULL << (SolidityParser::BooleanLiteral - 91))
        | (1ULL << (SolidityParser::DecimalNumber - 91))
        | (1ULL << (SolidityParser::HexNumber - 91))
        | (1ULL << (SolidityParser::HexLiteral - 91))
        | (1ULL << (SolidityParser::Identifier - 91))
        | (1ULL << (SolidityParser::StringLiteral - 91)))) != 0)) {
        setState(339);
        expressionList();
      }
      setState(342);
      match(SolidityParser::T__21);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionDefinitionContext ------------------------------------------------------------------

SolidityParser::FunctionDefinitionContext::FunctionDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SolidityParser::ParameterListContext* SolidityParser::FunctionDefinitionContext::parameterList() {
  return getRuleContext<SolidityParser::ParameterListContext>(0);
}

SolidityParser::ModifierListContext* SolidityParser::FunctionDefinitionContext::modifierList() {
  return getRuleContext<SolidityParser::ModifierListContext>(0);
}

SolidityParser::BlockContext* SolidityParser::FunctionDefinitionContext::block() {
  return getRuleContext<SolidityParser::BlockContext>(0);
}

SolidityParser::IdentifierContext* SolidityParser::FunctionDefinitionContext::identifier() {
  return getRuleContext<SolidityParser::IdentifierContext>(0);
}

SolidityParser::ReturnParametersContext* SolidityParser::FunctionDefinitionContext::returnParameters() {
  return getRuleContext<SolidityParser::ReturnParametersContext>(0);
}


size_t SolidityParser::FunctionDefinitionContext::getRuleIndex() const {
  return SolidityParser::RuleFunctionDefinition;
}


antlrcpp::Any SolidityParser::FunctionDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitFunctionDefinition(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::FunctionDefinitionContext* SolidityParser::functionDefinition() {
  FunctionDefinitionContext *_localctx = _tracker.createInstance<FunctionDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 36, SolidityParser::RuleFunctionDefinition);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(345);
    match(SolidityParser::T__27);
    setState(347);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SolidityParser::T__12

    || _la == SolidityParser::T__39 || _la == SolidityParser::Identifier) {
      setState(346);
      identifier();
    }
    setState(349);
    parameterList();
    setState(350);
    modifierList();
    setState(352);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SolidityParser::T__28) {
      setState(351);
      returnParameters();
    }
    setState(356);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SolidityParser::T__1: {
        setState(354);
        match(SolidityParser::T__1);
        break;
      }

      case SolidityParser::T__13: {
        setState(355);
        block();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ReturnParametersContext ------------------------------------------------------------------

SolidityParser::ReturnParametersContext::ReturnParametersContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SolidityParser::ParameterListContext* SolidityParser::ReturnParametersContext::parameterList() {
  return getRuleContext<SolidityParser::ParameterListContext>(0);
}


size_t SolidityParser::ReturnParametersContext::getRuleIndex() const {
  return SolidityParser::RuleReturnParameters;
}


antlrcpp::Any SolidityParser::ReturnParametersContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitReturnParameters(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::ReturnParametersContext* SolidityParser::returnParameters() {
  ReturnParametersContext *_localctx = _tracker.createInstance<ReturnParametersContext>(_ctx, getState());
  enterRule(_localctx, 38, SolidityParser::RuleReturnParameters);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(358);
    match(SolidityParser::T__28);
    setState(359);
    parameterList();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ModifierListContext ------------------------------------------------------------------

SolidityParser::ModifierListContext::ModifierListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SolidityParser::ModifierInvocationContext *> SolidityParser::ModifierListContext::modifierInvocation() {
  return getRuleContexts<SolidityParser::ModifierInvocationContext>();
}

SolidityParser::ModifierInvocationContext* SolidityParser::ModifierListContext::modifierInvocation(size_t i) {
  return getRuleContext<SolidityParser::ModifierInvocationContext>(i);
}

std::vector<SolidityParser::StateMutabilityContext *> SolidityParser::ModifierListContext::stateMutability() {
  return getRuleContexts<SolidityParser::StateMutabilityContext>();
}

SolidityParser::StateMutabilityContext* SolidityParser::ModifierListContext::stateMutability(size_t i) {
  return getRuleContext<SolidityParser::StateMutabilityContext>(i);
}

std::vector<tree::TerminalNode *> SolidityParser::ModifierListContext::ExternalKeyword() {
  return getTokens(SolidityParser::ExternalKeyword);
}

tree::TerminalNode* SolidityParser::ModifierListContext::ExternalKeyword(size_t i) {
  return getToken(SolidityParser::ExternalKeyword, i);
}

std::vector<tree::TerminalNode *> SolidityParser::ModifierListContext::PublicKeyword() {
  return getTokens(SolidityParser::PublicKeyword);
}

tree::TerminalNode* SolidityParser::ModifierListContext::PublicKeyword(size_t i) {
  return getToken(SolidityParser::PublicKeyword, i);
}

std::vector<tree::TerminalNode *> SolidityParser::ModifierListContext::InternalKeyword() {
  return getTokens(SolidityParser::InternalKeyword);
}

tree::TerminalNode* SolidityParser::ModifierListContext::InternalKeyword(size_t i) {
  return getToken(SolidityParser::InternalKeyword, i);
}

std::vector<tree::TerminalNode *> SolidityParser::ModifierListContext::PrivateKeyword() {
  return getTokens(SolidityParser::PrivateKeyword);
}

tree::TerminalNode* SolidityParser::ModifierListContext::PrivateKeyword(size_t i) {
  return getToken(SolidityParser::PrivateKeyword, i);
}


size_t SolidityParser::ModifierListContext::getRuleIndex() const {
  return SolidityParser::RuleModifierList;
}


antlrcpp::Any SolidityParser::ModifierListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitModifierList(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::ModifierListContext* SolidityParser::modifierList() {
  ModifierListContext *_localctx = _tracker.createInstance<ModifierListContext>(_ctx, getState());
  enterRule(_localctx, 40, SolidityParser::RuleModifierList);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(369);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SolidityParser::T__12

    || _la == SolidityParser::T__39 || ((((_la - 105) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 105)) & ((1ULL << (SolidityParser::ConstantKeyword - 105))
      | (1ULL << (SolidityParser::ExternalKeyword - 105))
      | (1ULL << (SolidityParser::InternalKeyword - 105))
      | (1ULL << (SolidityParser::PayableKeyword - 105))
      | (1ULL << (SolidityParser::PrivateKeyword - 105))
      | (1ULL << (SolidityParser::PublicKeyword - 105))
      | (1ULL << (SolidityParser::PureKeyword - 105))
      | (1ULL << (SolidityParser::ViewKeyword - 105))
      | (1ULL << (SolidityParser::Identifier - 105)))) != 0)) {
      setState(367);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case SolidityParser::T__12:
        case SolidityParser::T__39:
        case SolidityParser::Identifier: {
          setState(361);
          modifierInvocation();
          break;
        }

        case SolidityParser::ConstantKeyword:
        case SolidityParser::PayableKeyword:
        case SolidityParser::PureKeyword:
        case SolidityParser::ViewKeyword: {
          setState(362);
          stateMutability();
          break;
        }

        case SolidityParser::ExternalKeyword: {
          setState(363);
          match(SolidityParser::ExternalKeyword);
          break;
        }

        case SolidityParser::PublicKeyword: {
          setState(364);
          match(SolidityParser::PublicKeyword);
          break;
        }

        case SolidityParser::InternalKeyword: {
          setState(365);
          match(SolidityParser::InternalKeyword);
          break;
        }

        case SolidityParser::PrivateKeyword: {
          setState(366);
          match(SolidityParser::PrivateKeyword);
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(371);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EventDefinitionContext ------------------------------------------------------------------

SolidityParser::EventDefinitionContext::EventDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SolidityParser::IdentifierContext* SolidityParser::EventDefinitionContext::identifier() {
  return getRuleContext<SolidityParser::IdentifierContext>(0);
}

SolidityParser::EventParameterListContext* SolidityParser::EventDefinitionContext::eventParameterList() {
  return getRuleContext<SolidityParser::EventParameterListContext>(0);
}

tree::TerminalNode* SolidityParser::EventDefinitionContext::AnonymousKeyword() {
  return getToken(SolidityParser::AnonymousKeyword, 0);
}


size_t SolidityParser::EventDefinitionContext::getRuleIndex() const {
  return SolidityParser::RuleEventDefinition;
}


antlrcpp::Any SolidityParser::EventDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitEventDefinition(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::EventDefinitionContext* SolidityParser::eventDefinition() {
  EventDefinitionContext *_localctx = _tracker.createInstance<EventDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 42, SolidityParser::RuleEventDefinition);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(372);
    match(SolidityParser::T__29);
    setState(373);
    identifier();
    setState(374);
    eventParameterList();
    setState(376);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SolidityParser::AnonymousKeyword) {
      setState(375);
      match(SolidityParser::AnonymousKeyword);
    }
    setState(378);
    match(SolidityParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EnumValueContext ------------------------------------------------------------------

SolidityParser::EnumValueContext::EnumValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SolidityParser::IdentifierContext* SolidityParser::EnumValueContext::identifier() {
  return getRuleContext<SolidityParser::IdentifierContext>(0);
}


size_t SolidityParser::EnumValueContext::getRuleIndex() const {
  return SolidityParser::RuleEnumValue;
}


antlrcpp::Any SolidityParser::EnumValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitEnumValue(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::EnumValueContext* SolidityParser::enumValue() {
  EnumValueContext *_localctx = _tracker.createInstance<EnumValueContext>(_ctx, getState());
  enterRule(_localctx, 44, SolidityParser::RuleEnumValue);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(380);
    identifier();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EnumDefinitionContext ------------------------------------------------------------------

SolidityParser::EnumDefinitionContext::EnumDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SolidityParser::IdentifierContext* SolidityParser::EnumDefinitionContext::identifier() {
  return getRuleContext<SolidityParser::IdentifierContext>(0);
}

std::vector<SolidityParser::EnumValueContext *> SolidityParser::EnumDefinitionContext::enumValue() {
  return getRuleContexts<SolidityParser::EnumValueContext>();
}

SolidityParser::EnumValueContext* SolidityParser::EnumDefinitionContext::enumValue(size_t i) {
  return getRuleContext<SolidityParser::EnumValueContext>(i);
}


size_t SolidityParser::EnumDefinitionContext::getRuleIndex() const {
  return SolidityParser::RuleEnumDefinition;
}


antlrcpp::Any SolidityParser::EnumDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitEnumDefinition(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::EnumDefinitionContext* SolidityParser::enumDefinition() {
  EnumDefinitionContext *_localctx = _tracker.createInstance<EnumDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 46, SolidityParser::RuleEnumDefinition);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(382);
    match(SolidityParser::T__30);
    setState(383);
    identifier();
    setState(384);
    match(SolidityParser::T__13);
    setState(386);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SolidityParser::T__12

    || _la == SolidityParser::T__39 || _la == SolidityParser::Identifier) {
      setState(385);
      enumValue();
    }
    setState(392);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SolidityParser::T__14) {
      setState(388);
      match(SolidityParser::T__14);
      setState(389);
      enumValue();
      setState(394);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(395);
    match(SolidityParser::T__15);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParameterListContext ------------------------------------------------------------------

SolidityParser::ParameterListContext::ParameterListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SolidityParser::ParameterContext *> SolidityParser::ParameterListContext::parameter() {
  return getRuleContexts<SolidityParser::ParameterContext>();
}

SolidityParser::ParameterContext* SolidityParser::ParameterListContext::parameter(size_t i) {
  return getRuleContext<SolidityParser::ParameterContext>(i);
}


size_t SolidityParser::ParameterListContext::getRuleIndex() const {
  return SolidityParser::RuleParameterList;
}


antlrcpp::Any SolidityParser::ParameterListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitParameterList(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::ParameterListContext* SolidityParser::parameterList() {
  ParameterListContext *_localctx = _tracker.createInstance<ParameterListContext>(_ctx, getState());
  enterRule(_localctx, 48, SolidityParser::RuleParameterList);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(397);
    match(SolidityParser::T__20);
    setState(406);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SolidityParser::T__12)
      | (1ULL << SolidityParser::T__27)
      | (1ULL << SolidityParser::T__33)
      | (1ULL << SolidityParser::T__35)
      | (1ULL << SolidityParser::T__39)
      | (1ULL << SolidityParser::T__48)
      | (1ULL << SolidityParser::T__49)
      | (1ULL << SolidityParser::T__50)
      | (1ULL << SolidityParser::T__51))) != 0) || ((((_la - 91) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 91)) & ((1ULL << (SolidityParser::Int - 91))
      | (1ULL << (SolidityParser::Uint - 91))
      | (1ULL << (SolidityParser::Byte - 91))
      | (1ULL << (SolidityParser::Fixed - 91))
      | (1ULL << (SolidityParser::Ufixed - 91))
      | (1ULL << (SolidityParser::Identifier - 91)))) != 0)) {
      setState(398);
      parameter();
      setState(403);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == SolidityParser::T__14) {
        setState(399);
        match(SolidityParser::T__14);
        setState(400);
        parameter();
        setState(405);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(408);
    match(SolidityParser::T__21);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParameterContext ------------------------------------------------------------------

SolidityParser::ParameterContext::ParameterContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SolidityParser::TypeNameContext* SolidityParser::ParameterContext::typeName() {
  return getRuleContext<SolidityParser::TypeNameContext>(0);
}

SolidityParser::StorageLocationContext* SolidityParser::ParameterContext::storageLocation() {
  return getRuleContext<SolidityParser::StorageLocationContext>(0);
}

SolidityParser::IdentifierContext* SolidityParser::ParameterContext::identifier() {
  return getRuleContext<SolidityParser::IdentifierContext>(0);
}


size_t SolidityParser::ParameterContext::getRuleIndex() const {
  return SolidityParser::RuleParameter;
}


antlrcpp::Any SolidityParser::ParameterContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitParameter(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::ParameterContext* SolidityParser::parameter() {
  ParameterContext *_localctx = _tracker.createInstance<ParameterContext>(_ctx, getState());
  enterRule(_localctx, 50, SolidityParser::RuleParameter);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(410);
    typeName(0);
    setState(412);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx)) {
    case 1: {
      setState(411);
      storageLocation();
      break;
    }

    }
    setState(415);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SolidityParser::T__12

    || _la == SolidityParser::T__39 || _la == SolidityParser::Identifier) {
      setState(414);
      identifier();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EventParameterListContext ------------------------------------------------------------------

SolidityParser::EventParameterListContext::EventParameterListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SolidityParser::EventParameterContext *> SolidityParser::EventParameterListContext::eventParameter() {
  return getRuleContexts<SolidityParser::EventParameterContext>();
}

SolidityParser::EventParameterContext* SolidityParser::EventParameterListContext::eventParameter(size_t i) {
  return getRuleContext<SolidityParser::EventParameterContext>(i);
}


size_t SolidityParser::EventParameterListContext::getRuleIndex() const {
  return SolidityParser::RuleEventParameterList;
}


antlrcpp::Any SolidityParser::EventParameterListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitEventParameterList(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::EventParameterListContext* SolidityParser::eventParameterList() {
  EventParameterListContext *_localctx = _tracker.createInstance<EventParameterListContext>(_ctx, getState());
  enterRule(_localctx, 52, SolidityParser::RuleEventParameterList);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(417);
    match(SolidityParser::T__20);
    setState(426);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SolidityParser::T__12)
      | (1ULL << SolidityParser::T__27)
      | (1ULL << SolidityParser::T__33)
      | (1ULL << SolidityParser::T__35)
      | (1ULL << SolidityParser::T__39)
      | (1ULL << SolidityParser::T__48)
      | (1ULL << SolidityParser::T__49)
      | (1ULL << SolidityParser::T__50)
      | (1ULL << SolidityParser::T__51))) != 0) || ((((_la - 91) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 91)) & ((1ULL << (SolidityParser::Int - 91))
      | (1ULL << (SolidityParser::Uint - 91))
      | (1ULL << (SolidityParser::Byte - 91))
      | (1ULL << (SolidityParser::Fixed - 91))
      | (1ULL << (SolidityParser::Ufixed - 91))
      | (1ULL << (SolidityParser::Identifier - 91)))) != 0)) {
      setState(418);
      eventParameter();
      setState(423);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == SolidityParser::T__14) {
        setState(419);
        match(SolidityParser::T__14);
        setState(420);
        eventParameter();
        setState(425);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(428);
    match(SolidityParser::T__21);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EventParameterContext ------------------------------------------------------------------

SolidityParser::EventParameterContext::EventParameterContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SolidityParser::TypeNameContext* SolidityParser::EventParameterContext::typeName() {
  return getRuleContext<SolidityParser::TypeNameContext>(0);
}

tree::TerminalNode* SolidityParser::EventParameterContext::IndexedKeyword() {
  return getToken(SolidityParser::IndexedKeyword, 0);
}

SolidityParser::IdentifierContext* SolidityParser::EventParameterContext::identifier() {
  return getRuleContext<SolidityParser::IdentifierContext>(0);
}


size_t SolidityParser::EventParameterContext::getRuleIndex() const {
  return SolidityParser::RuleEventParameter;
}


antlrcpp::Any SolidityParser::EventParameterContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitEventParameter(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::EventParameterContext* SolidityParser::eventParameter() {
  EventParameterContext *_localctx = _tracker.createInstance<EventParameterContext>(_ctx, getState());
  enterRule(_localctx, 54, SolidityParser::RuleEventParameter);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(430);
    typeName(0);
    setState(432);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SolidityParser::IndexedKeyword) {
      setState(431);
      match(SolidityParser::IndexedKeyword);
    }
    setState(435);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SolidityParser::T__12

    || _la == SolidityParser::T__39 || _la == SolidityParser::Identifier) {
      setState(434);
      identifier();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionTypeParameterListContext ------------------------------------------------------------------

SolidityParser::FunctionTypeParameterListContext::FunctionTypeParameterListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SolidityParser::FunctionTypeParameterContext *> SolidityParser::FunctionTypeParameterListContext::functionTypeParameter() {
  return getRuleContexts<SolidityParser::FunctionTypeParameterContext>();
}

SolidityParser::FunctionTypeParameterContext* SolidityParser::FunctionTypeParameterListContext::functionTypeParameter(size_t i) {
  return getRuleContext<SolidityParser::FunctionTypeParameterContext>(i);
}


size_t SolidityParser::FunctionTypeParameterListContext::getRuleIndex() const {
  return SolidityParser::RuleFunctionTypeParameterList;
}


antlrcpp::Any SolidityParser::FunctionTypeParameterListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitFunctionTypeParameterList(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::FunctionTypeParameterListContext* SolidityParser::functionTypeParameterList() {
  FunctionTypeParameterListContext *_localctx = _tracker.createInstance<FunctionTypeParameterListContext>(_ctx, getState());
  enterRule(_localctx, 56, SolidityParser::RuleFunctionTypeParameterList);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(437);
    match(SolidityParser::T__20);
    setState(446);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SolidityParser::T__12)
      | (1ULL << SolidityParser::T__27)
      | (1ULL << SolidityParser::T__33)
      | (1ULL << SolidityParser::T__35)
      | (1ULL << SolidityParser::T__39)
      | (1ULL << SolidityParser::T__48)
      | (1ULL << SolidityParser::T__49)
      | (1ULL << SolidityParser::T__50)
      | (1ULL << SolidityParser::T__51))) != 0) || ((((_la - 91) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 91)) & ((1ULL << (SolidityParser::Int - 91))
      | (1ULL << (SolidityParser::Uint - 91))
      | (1ULL << (SolidityParser::Byte - 91))
      | (1ULL << (SolidityParser::Fixed - 91))
      | (1ULL << (SolidityParser::Ufixed - 91))
      | (1ULL << (SolidityParser::Identifier - 91)))) != 0)) {
      setState(438);
      functionTypeParameter();
      setState(443);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == SolidityParser::T__14) {
        setState(439);
        match(SolidityParser::T__14);
        setState(440);
        functionTypeParameter();
        setState(445);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(448);
    match(SolidityParser::T__21);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionTypeParameterContext ------------------------------------------------------------------

SolidityParser::FunctionTypeParameterContext::FunctionTypeParameterContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SolidityParser::TypeNameContext* SolidityParser::FunctionTypeParameterContext::typeName() {
  return getRuleContext<SolidityParser::TypeNameContext>(0);
}

SolidityParser::StorageLocationContext* SolidityParser::FunctionTypeParameterContext::storageLocation() {
  return getRuleContext<SolidityParser::StorageLocationContext>(0);
}


size_t SolidityParser::FunctionTypeParameterContext::getRuleIndex() const {
  return SolidityParser::RuleFunctionTypeParameter;
}


antlrcpp::Any SolidityParser::FunctionTypeParameterContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitFunctionTypeParameter(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::FunctionTypeParameterContext* SolidityParser::functionTypeParameter() {
  FunctionTypeParameterContext *_localctx = _tracker.createInstance<FunctionTypeParameterContext>(_ctx, getState());
  enterRule(_localctx, 58, SolidityParser::RuleFunctionTypeParameter);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(450);
    typeName(0);
    setState(452);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SolidityParser::T__37)
      | (1ULL << SolidityParser::T__38)
      | (1ULL << SolidityParser::T__39))) != 0)) {
      setState(451);
      storageLocation();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableDeclarationContext ------------------------------------------------------------------

SolidityParser::VariableDeclarationContext::VariableDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SolidityParser::TypeNameContext* SolidityParser::VariableDeclarationContext::typeName() {
  return getRuleContext<SolidityParser::TypeNameContext>(0);
}

SolidityParser::IdentifierContext* SolidityParser::VariableDeclarationContext::identifier() {
  return getRuleContext<SolidityParser::IdentifierContext>(0);
}

SolidityParser::StorageLocationContext* SolidityParser::VariableDeclarationContext::storageLocation() {
  return getRuleContext<SolidityParser::StorageLocationContext>(0);
}


size_t SolidityParser::VariableDeclarationContext::getRuleIndex() const {
  return SolidityParser::RuleVariableDeclaration;
}


antlrcpp::Any SolidityParser::VariableDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitVariableDeclaration(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::VariableDeclarationContext* SolidityParser::variableDeclaration() {
  VariableDeclarationContext *_localctx = _tracker.createInstance<VariableDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 60, SolidityParser::RuleVariableDeclaration);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(454);
    typeName(0);
    setState(456);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 44, _ctx)) {
    case 1: {
      setState(455);
      storageLocation();
      break;
    }

    }
    setState(458);
    identifier();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeNameContext ------------------------------------------------------------------

SolidityParser::TypeNameContext::TypeNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SolidityParser::ElementaryTypeNameContext* SolidityParser::TypeNameContext::elementaryTypeName() {
  return getRuleContext<SolidityParser::ElementaryTypeNameContext>(0);
}

SolidityParser::UserDefinedTypeNameContext* SolidityParser::TypeNameContext::userDefinedTypeName() {
  return getRuleContext<SolidityParser::UserDefinedTypeNameContext>(0);
}

SolidityParser::MappingContext* SolidityParser::TypeNameContext::mapping() {
  return getRuleContext<SolidityParser::MappingContext>(0);
}

SolidityParser::FunctionTypeNameContext* SolidityParser::TypeNameContext::functionTypeName() {
  return getRuleContext<SolidityParser::FunctionTypeNameContext>(0);
}

tree::TerminalNode* SolidityParser::TypeNameContext::PayableKeyword() {
  return getToken(SolidityParser::PayableKeyword, 0);
}

SolidityParser::TypeNameContext* SolidityParser::TypeNameContext::typeName() {
  return getRuleContext<SolidityParser::TypeNameContext>(0);
}

SolidityParser::ExpressionContext* SolidityParser::TypeNameContext::expression() {
  return getRuleContext<SolidityParser::ExpressionContext>(0);
}


size_t SolidityParser::TypeNameContext::getRuleIndex() const {
  return SolidityParser::RuleTypeName;
}


antlrcpp::Any SolidityParser::TypeNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitTypeName(this);
  else
    return visitor->visitChildren(this);
}


SolidityParser::TypeNameContext* SolidityParser::typeName() {
   return typeName(0);
}

SolidityParser::TypeNameContext* SolidityParser::typeName(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  SolidityParser::TypeNameContext *_localctx = _tracker.createInstance<TypeNameContext>(_ctx, parentState);
  SolidityParser::TypeNameContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 62;
  enterRecursionRule(_localctx, 62, SolidityParser::RuleTypeName, precedence);

    size_t _la = 0;

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(467);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 45, _ctx)) {
    case 1: {
      setState(461);
      elementaryTypeName();
      break;
    }

    case 2: {
      setState(462);
      userDefinedTypeName();
      break;
    }

    case 3: {
      setState(463);
      mapping();
      break;
    }

    case 4: {
      setState(464);
      functionTypeName();
      break;
    }

    case 5: {
      setState(465);
      match(SolidityParser::T__33);
      setState(466);
      match(SolidityParser::PayableKeyword);
      break;
    }

    }
    _ctx->stop = _input->LT(-1);
    setState(477);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<TypeNameContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleTypeName);
        setState(469);

        if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
        setState(470);
        match(SolidityParser::T__31);
        setState(472);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << SolidityParser::T__3)
          | (1ULL << SolidityParser::T__12)
          | (1ULL << SolidityParser::T__20)
          | (1ULL << SolidityParser::T__31)
          | (1ULL << SolidityParser::T__33)
          | (1ULL << SolidityParser::T__39)
          | (1ULL << SolidityParser::T__48)
          | (1ULL << SolidityParser::T__49)
          | (1ULL << SolidityParser::T__50)
          | (1ULL << SolidityParser::T__51)
          | (1ULL << SolidityParser::T__52)
          | (1ULL << SolidityParser::T__53)
          | (1ULL << SolidityParser::T__54)
          | (1ULL << SolidityParser::T__55)
          | (1ULL << SolidityParser::T__56)
          | (1ULL << SolidityParser::T__57)
          | (1ULL << SolidityParser::T__58)
          | (1ULL << SolidityParser::T__59))) != 0) || ((((_la - 91) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 91)) & ((1ULL << (SolidityParser::Int - 91))
          | (1ULL << (SolidityParser::Uint - 91))
          | (1ULL << (SolidityParser::Byte - 91))
          | (1ULL << (SolidityParser::Fixed - 91))
          | (1ULL << (SolidityParser::Ufixed - 91))
          | (1ULL << (SolidityParser::BooleanLiteral - 91))
          | (1ULL << (SolidityParser::DecimalNumber - 91))
          | (1ULL << (SolidityParser::HexNumber - 91))
          | (1ULL << (SolidityParser::HexLiteral - 91))
          | (1ULL << (SolidityParser::Identifier - 91))
          | (1ULL << (SolidityParser::StringLiteral - 91)))) != 0)) {
          setState(471);
          expression(0);
        }
        setState(474);
        match(SolidityParser::T__32); 
      }
      setState(479);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- UserDefinedTypeNameContext ------------------------------------------------------------------

SolidityParser::UserDefinedTypeNameContext::UserDefinedTypeNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SolidityParser::IdentifierContext *> SolidityParser::UserDefinedTypeNameContext::identifier() {
  return getRuleContexts<SolidityParser::IdentifierContext>();
}

SolidityParser::IdentifierContext* SolidityParser::UserDefinedTypeNameContext::identifier(size_t i) {
  return getRuleContext<SolidityParser::IdentifierContext>(i);
}


size_t SolidityParser::UserDefinedTypeNameContext::getRuleIndex() const {
  return SolidityParser::RuleUserDefinedTypeName;
}


antlrcpp::Any SolidityParser::UserDefinedTypeNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitUserDefinedTypeName(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::UserDefinedTypeNameContext* SolidityParser::userDefinedTypeName() {
  UserDefinedTypeNameContext *_localctx = _tracker.createInstance<UserDefinedTypeNameContext>(_ctx, getState());
  enterRule(_localctx, 64, SolidityParser::RuleUserDefinedTypeName);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(480);
    identifier();
    setState(485);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 48, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(481);
        match(SolidityParser::T__34);
        setState(482);
        identifier(); 
      }
      setState(487);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 48, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MappingContext ------------------------------------------------------------------

SolidityParser::MappingContext::MappingContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SolidityParser::ElementaryTypeNameContext* SolidityParser::MappingContext::elementaryTypeName() {
  return getRuleContext<SolidityParser::ElementaryTypeNameContext>(0);
}

SolidityParser::TypeNameContext* SolidityParser::MappingContext::typeName() {
  return getRuleContext<SolidityParser::TypeNameContext>(0);
}


size_t SolidityParser::MappingContext::getRuleIndex() const {
  return SolidityParser::RuleMapping;
}


antlrcpp::Any SolidityParser::MappingContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitMapping(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::MappingContext* SolidityParser::mapping() {
  MappingContext *_localctx = _tracker.createInstance<MappingContext>(_ctx, getState());
  enterRule(_localctx, 66, SolidityParser::RuleMapping);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(488);
    match(SolidityParser::T__35);
    setState(489);
    match(SolidityParser::T__20);
    setState(490);
    elementaryTypeName();
    setState(491);
    match(SolidityParser::T__36);
    setState(492);
    typeName(0);
    setState(493);
    match(SolidityParser::T__21);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionTypeNameContext ------------------------------------------------------------------

SolidityParser::FunctionTypeNameContext::FunctionTypeNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SolidityParser::FunctionTypeParameterListContext *> SolidityParser::FunctionTypeNameContext::functionTypeParameterList() {
  return getRuleContexts<SolidityParser::FunctionTypeParameterListContext>();
}

SolidityParser::FunctionTypeParameterListContext* SolidityParser::FunctionTypeNameContext::functionTypeParameterList(size_t i) {
  return getRuleContext<SolidityParser::FunctionTypeParameterListContext>(i);
}

std::vector<tree::TerminalNode *> SolidityParser::FunctionTypeNameContext::InternalKeyword() {
  return getTokens(SolidityParser::InternalKeyword);
}

tree::TerminalNode* SolidityParser::FunctionTypeNameContext::InternalKeyword(size_t i) {
  return getToken(SolidityParser::InternalKeyword, i);
}

std::vector<tree::TerminalNode *> SolidityParser::FunctionTypeNameContext::ExternalKeyword() {
  return getTokens(SolidityParser::ExternalKeyword);
}

tree::TerminalNode* SolidityParser::FunctionTypeNameContext::ExternalKeyword(size_t i) {
  return getToken(SolidityParser::ExternalKeyword, i);
}

std::vector<SolidityParser::StateMutabilityContext *> SolidityParser::FunctionTypeNameContext::stateMutability() {
  return getRuleContexts<SolidityParser::StateMutabilityContext>();
}

SolidityParser::StateMutabilityContext* SolidityParser::FunctionTypeNameContext::stateMutability(size_t i) {
  return getRuleContext<SolidityParser::StateMutabilityContext>(i);
}


size_t SolidityParser::FunctionTypeNameContext::getRuleIndex() const {
  return SolidityParser::RuleFunctionTypeName;
}


antlrcpp::Any SolidityParser::FunctionTypeNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitFunctionTypeName(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::FunctionTypeNameContext* SolidityParser::functionTypeName() {
  FunctionTypeNameContext *_localctx = _tracker.createInstance<FunctionTypeNameContext>(_ctx, getState());
  enterRule(_localctx, 68, SolidityParser::RuleFunctionTypeName);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(495);
    match(SolidityParser::T__27);
    setState(496);
    functionTypeParameterList();
    setState(502);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 50, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(500);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case SolidityParser::InternalKeyword: {
            setState(497);
            match(SolidityParser::InternalKeyword);
            break;
          }

          case SolidityParser::ExternalKeyword: {
            setState(498);
            match(SolidityParser::ExternalKeyword);
            break;
          }

          case SolidityParser::ConstantKeyword:
          case SolidityParser::PayableKeyword:
          case SolidityParser::PureKeyword:
          case SolidityParser::ViewKeyword: {
            setState(499);
            stateMutability();
            break;
          }

        default:
          throw NoViableAltException(this);
        } 
      }
      setState(504);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 50, _ctx);
    }
    setState(507);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 51, _ctx)) {
    case 1: {
      setState(505);
      match(SolidityParser::T__28);
      setState(506);
      functionTypeParameterList();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StorageLocationContext ------------------------------------------------------------------

SolidityParser::StorageLocationContext::StorageLocationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SolidityParser::StorageLocationContext::getRuleIndex() const {
  return SolidityParser::RuleStorageLocation;
}


antlrcpp::Any SolidityParser::StorageLocationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitStorageLocation(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::StorageLocationContext* SolidityParser::storageLocation() {
  StorageLocationContext *_localctx = _tracker.createInstance<StorageLocationContext>(_ctx, getState());
  enterRule(_localctx, 70, SolidityParser::RuleStorageLocation);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(509);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SolidityParser::T__37)
      | (1ULL << SolidityParser::T__38)
      | (1ULL << SolidityParser::T__39))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StateMutabilityContext ------------------------------------------------------------------

SolidityParser::StateMutabilityContext::StateMutabilityContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SolidityParser::StateMutabilityContext::PureKeyword() {
  return getToken(SolidityParser::PureKeyword, 0);
}

tree::TerminalNode* SolidityParser::StateMutabilityContext::ConstantKeyword() {
  return getToken(SolidityParser::ConstantKeyword, 0);
}

tree::TerminalNode* SolidityParser::StateMutabilityContext::ViewKeyword() {
  return getToken(SolidityParser::ViewKeyword, 0);
}

tree::TerminalNode* SolidityParser::StateMutabilityContext::PayableKeyword() {
  return getToken(SolidityParser::PayableKeyword, 0);
}


size_t SolidityParser::StateMutabilityContext::getRuleIndex() const {
  return SolidityParser::RuleStateMutability;
}


antlrcpp::Any SolidityParser::StateMutabilityContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitStateMutability(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::StateMutabilityContext* SolidityParser::stateMutability() {
  StateMutabilityContext *_localctx = _tracker.createInstance<StateMutabilityContext>(_ctx, getState());
  enterRule(_localctx, 72, SolidityParser::RuleStateMutability);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(511);
    _la = _input->LA(1);
    if (!(((((_la - 105) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 105)) & ((1ULL << (SolidityParser::ConstantKeyword - 105))
      | (1ULL << (SolidityParser::PayableKeyword - 105))
      | (1ULL << (SolidityParser::PureKeyword - 105))
      | (1ULL << (SolidityParser::ViewKeyword - 105)))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

SolidityParser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SolidityParser::StatementContext *> SolidityParser::BlockContext::statement() {
  return getRuleContexts<SolidityParser::StatementContext>();
}

SolidityParser::StatementContext* SolidityParser::BlockContext::statement(size_t i) {
  return getRuleContext<SolidityParser::StatementContext>(i);
}


size_t SolidityParser::BlockContext::getRuleIndex() const {
  return SolidityParser::RuleBlock;
}


antlrcpp::Any SolidityParser::BlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitBlock(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::BlockContext* SolidityParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 74, SolidityParser::RuleBlock);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(513);
    match(SolidityParser::T__13);
    setState(517);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SolidityParser::T__3)
      | (1ULL << SolidityParser::T__12)
      | (1ULL << SolidityParser::T__13)
      | (1ULL << SolidityParser::T__20)
      | (1ULL << SolidityParser::T__23)
      | (1ULL << SolidityParser::T__27)
      | (1ULL << SolidityParser::T__31)
      | (1ULL << SolidityParser::T__33)
      | (1ULL << SolidityParser::T__35)
      | (1ULL << SolidityParser::T__39)
      | (1ULL << SolidityParser::T__40)
      | (1ULL << SolidityParser::T__42)
      | (1ULL << SolidityParser::T__43)
      | (1ULL << SolidityParser::T__44)
      | (1ULL << SolidityParser::T__45)
      | (1ULL << SolidityParser::T__46)
      | (1ULL << SolidityParser::T__47)
      | (1ULL << SolidityParser::T__48)
      | (1ULL << SolidityParser::T__49)
      | (1ULL << SolidityParser::T__50)
      | (1ULL << SolidityParser::T__51)
      | (1ULL << SolidityParser::T__52)
      | (1ULL << SolidityParser::T__53)
      | (1ULL << SolidityParser::T__54)
      | (1ULL << SolidityParser::T__55)
      | (1ULL << SolidityParser::T__56)
      | (1ULL << SolidityParser::T__57)
      | (1ULL << SolidityParser::T__58)
      | (1ULL << SolidityParser::T__59))) != 0) || ((((_la - 91) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 91)) & ((1ULL << (SolidityParser::Int - 91))
      | (1ULL << (SolidityParser::Uint - 91))
      | (1ULL << (SolidityParser::Byte - 91))
      | (1ULL << (SolidityParser::Fixed - 91))
      | (1ULL << (SolidityParser::Ufixed - 91))
      | (1ULL << (SolidityParser::BooleanLiteral - 91))
      | (1ULL << (SolidityParser::DecimalNumber - 91))
      | (1ULL << (SolidityParser::HexNumber - 91))
      | (1ULL << (SolidityParser::HexLiteral - 91))
      | (1ULL << (SolidityParser::BreakKeyword - 91))
      | (1ULL << (SolidityParser::ContinueKeyword - 91))
      | (1ULL << (SolidityParser::Identifier - 91))
      | (1ULL << (SolidityParser::StringLiteral - 91)))) != 0)) {
      setState(514);
      statement();
      setState(519);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(520);
    match(SolidityParser::T__15);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

SolidityParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SolidityParser::IfStatementContext* SolidityParser::StatementContext::ifStatement() {
  return getRuleContext<SolidityParser::IfStatementContext>(0);
}

SolidityParser::WhileStatementContext* SolidityParser::StatementContext::whileStatement() {
  return getRuleContext<SolidityParser::WhileStatementContext>(0);
}

SolidityParser::ForStatementContext* SolidityParser::StatementContext::forStatement() {
  return getRuleContext<SolidityParser::ForStatementContext>(0);
}

SolidityParser::BlockContext* SolidityParser::StatementContext::block() {
  return getRuleContext<SolidityParser::BlockContext>(0);
}

SolidityParser::InlineAssemblyStatementContext* SolidityParser::StatementContext::inlineAssemblyStatement() {
  return getRuleContext<SolidityParser::InlineAssemblyStatementContext>(0);
}

SolidityParser::DoWhileStatementContext* SolidityParser::StatementContext::doWhileStatement() {
  return getRuleContext<SolidityParser::DoWhileStatementContext>(0);
}

SolidityParser::ContinueStatementContext* SolidityParser::StatementContext::continueStatement() {
  return getRuleContext<SolidityParser::ContinueStatementContext>(0);
}

SolidityParser::BreakStatementContext* SolidityParser::StatementContext::breakStatement() {
  return getRuleContext<SolidityParser::BreakStatementContext>(0);
}

SolidityParser::ReturnStatementContext* SolidityParser::StatementContext::returnStatement() {
  return getRuleContext<SolidityParser::ReturnStatementContext>(0);
}

SolidityParser::ThrowStatementContext* SolidityParser::StatementContext::throwStatement() {
  return getRuleContext<SolidityParser::ThrowStatementContext>(0);
}

SolidityParser::EmitStatementContext* SolidityParser::StatementContext::emitStatement() {
  return getRuleContext<SolidityParser::EmitStatementContext>(0);
}

SolidityParser::SimpleStatementContext* SolidityParser::StatementContext::simpleStatement() {
  return getRuleContext<SolidityParser::SimpleStatementContext>(0);
}


size_t SolidityParser::StatementContext::getRuleIndex() const {
  return SolidityParser::RuleStatement;
}


antlrcpp::Any SolidityParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::StatementContext* SolidityParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 76, SolidityParser::RuleStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(534);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SolidityParser::T__40: {
        enterOuterAlt(_localctx, 1);
        setState(522);
        ifStatement();
        break;
      }

      case SolidityParser::T__42: {
        enterOuterAlt(_localctx, 2);
        setState(523);
        whileStatement();
        break;
      }

      case SolidityParser::T__23: {
        enterOuterAlt(_localctx, 3);
        setState(524);
        forStatement();
        break;
      }

      case SolidityParser::T__13: {
        enterOuterAlt(_localctx, 4);
        setState(525);
        block();
        break;
      }

      case SolidityParser::T__43: {
        enterOuterAlt(_localctx, 5);
        setState(526);
        inlineAssemblyStatement();
        break;
      }

      case SolidityParser::T__44: {
        enterOuterAlt(_localctx, 6);
        setState(527);
        doWhileStatement();
        break;
      }

      case SolidityParser::ContinueKeyword: {
        enterOuterAlt(_localctx, 7);
        setState(528);
        continueStatement();
        break;
      }

      case SolidityParser::BreakKeyword: {
        enterOuterAlt(_localctx, 8);
        setState(529);
        breakStatement();
        break;
      }

      case SolidityParser::T__45: {
        enterOuterAlt(_localctx, 9);
        setState(530);
        returnStatement();
        break;
      }

      case SolidityParser::T__46: {
        enterOuterAlt(_localctx, 10);
        setState(531);
        throwStatement();
        break;
      }

      case SolidityParser::T__47: {
        enterOuterAlt(_localctx, 11);
        setState(532);
        emitStatement();
        break;
      }

      case SolidityParser::T__3:
      case SolidityParser::T__12:
      case SolidityParser::T__20:
      case SolidityParser::T__27:
      case SolidityParser::T__31:
      case SolidityParser::T__33:
      case SolidityParser::T__35:
      case SolidityParser::T__39:
      case SolidityParser::T__48:
      case SolidityParser::T__49:
      case SolidityParser::T__50:
      case SolidityParser::T__51:
      case SolidityParser::T__52:
      case SolidityParser::T__53:
      case SolidityParser::T__54:
      case SolidityParser::T__55:
      case SolidityParser::T__56:
      case SolidityParser::T__57:
      case SolidityParser::T__58:
      case SolidityParser::T__59:
      case SolidityParser::Int:
      case SolidityParser::Uint:
      case SolidityParser::Byte:
      case SolidityParser::Fixed:
      case SolidityParser::Ufixed:
      case SolidityParser::BooleanLiteral:
      case SolidityParser::DecimalNumber:
      case SolidityParser::HexNumber:
      case SolidityParser::HexLiteral:
      case SolidityParser::Identifier:
      case SolidityParser::StringLiteral: {
        enterOuterAlt(_localctx, 12);
        setState(533);
        simpleStatement();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionStatementContext ------------------------------------------------------------------

SolidityParser::ExpressionStatementContext::ExpressionStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SolidityParser::ExpressionContext* SolidityParser::ExpressionStatementContext::expression() {
  return getRuleContext<SolidityParser::ExpressionContext>(0);
}


size_t SolidityParser::ExpressionStatementContext::getRuleIndex() const {
  return SolidityParser::RuleExpressionStatement;
}


antlrcpp::Any SolidityParser::ExpressionStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitExpressionStatement(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::ExpressionStatementContext* SolidityParser::expressionStatement() {
  ExpressionStatementContext *_localctx = _tracker.createInstance<ExpressionStatementContext>(_ctx, getState());
  enterRule(_localctx, 78, SolidityParser::RuleExpressionStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(536);
    expression(0);
    setState(537);
    match(SolidityParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IfStatementContext ------------------------------------------------------------------

SolidityParser::IfStatementContext::IfStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SolidityParser::ExpressionContext* SolidityParser::IfStatementContext::expression() {
  return getRuleContext<SolidityParser::ExpressionContext>(0);
}

std::vector<SolidityParser::StatementContext *> SolidityParser::IfStatementContext::statement() {
  return getRuleContexts<SolidityParser::StatementContext>();
}

SolidityParser::StatementContext* SolidityParser::IfStatementContext::statement(size_t i) {
  return getRuleContext<SolidityParser::StatementContext>(i);
}


size_t SolidityParser::IfStatementContext::getRuleIndex() const {
  return SolidityParser::RuleIfStatement;
}


antlrcpp::Any SolidityParser::IfStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitIfStatement(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::IfStatementContext* SolidityParser::ifStatement() {
  IfStatementContext *_localctx = _tracker.createInstance<IfStatementContext>(_ctx, getState());
  enterRule(_localctx, 80, SolidityParser::RuleIfStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(539);
    match(SolidityParser::T__40);
    setState(540);
    match(SolidityParser::T__20);
    setState(541);
    expression(0);
    setState(542);
    match(SolidityParser::T__21);
    setState(543);
    statement();
    setState(546);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 54, _ctx)) {
    case 1: {
      setState(544);
      match(SolidityParser::T__41);
      setState(545);
      statement();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- WhileStatementContext ------------------------------------------------------------------

SolidityParser::WhileStatementContext::WhileStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SolidityParser::ExpressionContext* SolidityParser::WhileStatementContext::expression() {
  return getRuleContext<SolidityParser::ExpressionContext>(0);
}

SolidityParser::StatementContext* SolidityParser::WhileStatementContext::statement() {
  return getRuleContext<SolidityParser::StatementContext>(0);
}


size_t SolidityParser::WhileStatementContext::getRuleIndex() const {
  return SolidityParser::RuleWhileStatement;
}


antlrcpp::Any SolidityParser::WhileStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitWhileStatement(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::WhileStatementContext* SolidityParser::whileStatement() {
  WhileStatementContext *_localctx = _tracker.createInstance<WhileStatementContext>(_ctx, getState());
  enterRule(_localctx, 82, SolidityParser::RuleWhileStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(548);
    match(SolidityParser::T__42);
    setState(549);
    match(SolidityParser::T__20);
    setState(550);
    expression(0);
    setState(551);
    match(SolidityParser::T__21);
    setState(552);
    statement();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SimpleStatementContext ------------------------------------------------------------------

SolidityParser::SimpleStatementContext::SimpleStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SolidityParser::VariableDeclarationStatementContext* SolidityParser::SimpleStatementContext::variableDeclarationStatement() {
  return getRuleContext<SolidityParser::VariableDeclarationStatementContext>(0);
}

SolidityParser::ExpressionStatementContext* SolidityParser::SimpleStatementContext::expressionStatement() {
  return getRuleContext<SolidityParser::ExpressionStatementContext>(0);
}


size_t SolidityParser::SimpleStatementContext::getRuleIndex() const {
  return SolidityParser::RuleSimpleStatement;
}


antlrcpp::Any SolidityParser::SimpleStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitSimpleStatement(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::SimpleStatementContext* SolidityParser::simpleStatement() {
  SimpleStatementContext *_localctx = _tracker.createInstance<SimpleStatementContext>(_ctx, getState());
  enterRule(_localctx, 84, SolidityParser::RuleSimpleStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(556);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 55, _ctx)) {
    case 1: {
      setState(554);
      variableDeclarationStatement();
      break;
    }

    case 2: {
      setState(555);
      expressionStatement();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ForStatementContext ------------------------------------------------------------------

SolidityParser::ForStatementContext::ForStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SolidityParser::StatementContext* SolidityParser::ForStatementContext::statement() {
  return getRuleContext<SolidityParser::StatementContext>(0);
}

SolidityParser::SimpleStatementContext* SolidityParser::ForStatementContext::simpleStatement() {
  return getRuleContext<SolidityParser::SimpleStatementContext>(0);
}

SolidityParser::ExpressionStatementContext* SolidityParser::ForStatementContext::expressionStatement() {
  return getRuleContext<SolidityParser::ExpressionStatementContext>(0);
}

SolidityParser::ExpressionContext* SolidityParser::ForStatementContext::expression() {
  return getRuleContext<SolidityParser::ExpressionContext>(0);
}


size_t SolidityParser::ForStatementContext::getRuleIndex() const {
  return SolidityParser::RuleForStatement;
}


antlrcpp::Any SolidityParser::ForStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitForStatement(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::ForStatementContext* SolidityParser::forStatement() {
  ForStatementContext *_localctx = _tracker.createInstance<ForStatementContext>(_ctx, getState());
  enterRule(_localctx, 86, SolidityParser::RuleForStatement);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(558);
    match(SolidityParser::T__23);
    setState(559);
    match(SolidityParser::T__20);
    setState(562);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SolidityParser::T__3:
      case SolidityParser::T__12:
      case SolidityParser::T__20:
      case SolidityParser::T__27:
      case SolidityParser::T__31:
      case SolidityParser::T__33:
      case SolidityParser::T__35:
      case SolidityParser::T__39:
      case SolidityParser::T__48:
      case SolidityParser::T__49:
      case SolidityParser::T__50:
      case SolidityParser::T__51:
      case SolidityParser::T__52:
      case SolidityParser::T__53:
      case SolidityParser::T__54:
      case SolidityParser::T__55:
      case SolidityParser::T__56:
      case SolidityParser::T__57:
      case SolidityParser::T__58:
      case SolidityParser::T__59:
      case SolidityParser::Int:
      case SolidityParser::Uint:
      case SolidityParser::Byte:
      case SolidityParser::Fixed:
      case SolidityParser::Ufixed:
      case SolidityParser::BooleanLiteral:
      case SolidityParser::DecimalNumber:
      case SolidityParser::HexNumber:
      case SolidityParser::HexLiteral:
      case SolidityParser::Identifier:
      case SolidityParser::StringLiteral: {
        setState(560);
        simpleStatement();
        break;
      }

      case SolidityParser::T__1: {
        setState(561);
        match(SolidityParser::T__1);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(566);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SolidityParser::T__3:
      case SolidityParser::T__12:
      case SolidityParser::T__20:
      case SolidityParser::T__31:
      case SolidityParser::T__33:
      case SolidityParser::T__39:
      case SolidityParser::T__48:
      case SolidityParser::T__49:
      case SolidityParser::T__50:
      case SolidityParser::T__51:
      case SolidityParser::T__52:
      case SolidityParser::T__53:
      case SolidityParser::T__54:
      case SolidityParser::T__55:
      case SolidityParser::T__56:
      case SolidityParser::T__57:
      case SolidityParser::T__58:
      case SolidityParser::T__59:
      case SolidityParser::Int:
      case SolidityParser::Uint:
      case SolidityParser::Byte:
      case SolidityParser::Fixed:
      case SolidityParser::Ufixed:
      case SolidityParser::BooleanLiteral:
      case SolidityParser::DecimalNumber:
      case SolidityParser::HexNumber:
      case SolidityParser::HexLiteral:
      case SolidityParser::Identifier:
      case SolidityParser::StringLiteral: {
        setState(564);
        expressionStatement();
        break;
      }

      case SolidityParser::T__1: {
        setState(565);
        match(SolidityParser::T__1);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(569);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SolidityParser::T__3)
      | (1ULL << SolidityParser::T__12)
      | (1ULL << SolidityParser::T__20)
      | (1ULL << SolidityParser::T__31)
      | (1ULL << SolidityParser::T__33)
      | (1ULL << SolidityParser::T__39)
      | (1ULL << SolidityParser::T__48)
      | (1ULL << SolidityParser::T__49)
      | (1ULL << SolidityParser::T__50)
      | (1ULL << SolidityParser::T__51)
      | (1ULL << SolidityParser::T__52)
      | (1ULL << SolidityParser::T__53)
      | (1ULL << SolidityParser::T__54)
      | (1ULL << SolidityParser::T__55)
      | (1ULL << SolidityParser::T__56)
      | (1ULL << SolidityParser::T__57)
      | (1ULL << SolidityParser::T__58)
      | (1ULL << SolidityParser::T__59))) != 0) || ((((_la - 91) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 91)) & ((1ULL << (SolidityParser::Int - 91))
      | (1ULL << (SolidityParser::Uint - 91))
      | (1ULL << (SolidityParser::Byte - 91))
      | (1ULL << (SolidityParser::Fixed - 91))
      | (1ULL << (SolidityParser::Ufixed - 91))
      | (1ULL << (SolidityParser::BooleanLiteral - 91))
      | (1ULL << (SolidityParser::DecimalNumber - 91))
      | (1ULL << (SolidityParser::HexNumber - 91))
      | (1ULL << (SolidityParser::HexLiteral - 91))
      | (1ULL << (SolidityParser::Identifier - 91))
      | (1ULL << (SolidityParser::StringLiteral - 91)))) != 0)) {
      setState(568);
      expression(0);
    }
    setState(571);
    match(SolidityParser::T__21);
    setState(572);
    statement();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InlineAssemblyStatementContext ------------------------------------------------------------------

SolidityParser::InlineAssemblyStatementContext::InlineAssemblyStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SolidityParser::AssemblyBlockContext* SolidityParser::InlineAssemblyStatementContext::assemblyBlock() {
  return getRuleContext<SolidityParser::AssemblyBlockContext>(0);
}

tree::TerminalNode* SolidityParser::InlineAssemblyStatementContext::StringLiteral() {
  return getToken(SolidityParser::StringLiteral, 0);
}


size_t SolidityParser::InlineAssemblyStatementContext::getRuleIndex() const {
  return SolidityParser::RuleInlineAssemblyStatement;
}


antlrcpp::Any SolidityParser::InlineAssemblyStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitInlineAssemblyStatement(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::InlineAssemblyStatementContext* SolidityParser::inlineAssemblyStatement() {
  InlineAssemblyStatementContext *_localctx = _tracker.createInstance<InlineAssemblyStatementContext>(_ctx, getState());
  enterRule(_localctx, 88, SolidityParser::RuleInlineAssemblyStatement);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(574);
    match(SolidityParser::T__43);
    setState(576);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SolidityParser::StringLiteral) {
      setState(575);
      match(SolidityParser::StringLiteral);
    }
    setState(578);
    assemblyBlock();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DoWhileStatementContext ------------------------------------------------------------------

SolidityParser::DoWhileStatementContext::DoWhileStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SolidityParser::StatementContext* SolidityParser::DoWhileStatementContext::statement() {
  return getRuleContext<SolidityParser::StatementContext>(0);
}

SolidityParser::ExpressionContext* SolidityParser::DoWhileStatementContext::expression() {
  return getRuleContext<SolidityParser::ExpressionContext>(0);
}


size_t SolidityParser::DoWhileStatementContext::getRuleIndex() const {
  return SolidityParser::RuleDoWhileStatement;
}


antlrcpp::Any SolidityParser::DoWhileStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitDoWhileStatement(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::DoWhileStatementContext* SolidityParser::doWhileStatement() {
  DoWhileStatementContext *_localctx = _tracker.createInstance<DoWhileStatementContext>(_ctx, getState());
  enterRule(_localctx, 90, SolidityParser::RuleDoWhileStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(580);
    match(SolidityParser::T__44);
    setState(581);
    statement();
    setState(582);
    match(SolidityParser::T__42);
    setState(583);
    match(SolidityParser::T__20);
    setState(584);
    expression(0);
    setState(585);
    match(SolidityParser::T__21);
    setState(586);
    match(SolidityParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ContinueStatementContext ------------------------------------------------------------------

SolidityParser::ContinueStatementContext::ContinueStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SolidityParser::ContinueStatementContext::ContinueKeyword() {
  return getToken(SolidityParser::ContinueKeyword, 0);
}


size_t SolidityParser::ContinueStatementContext::getRuleIndex() const {
  return SolidityParser::RuleContinueStatement;
}


antlrcpp::Any SolidityParser::ContinueStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitContinueStatement(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::ContinueStatementContext* SolidityParser::continueStatement() {
  ContinueStatementContext *_localctx = _tracker.createInstance<ContinueStatementContext>(_ctx, getState());
  enterRule(_localctx, 92, SolidityParser::RuleContinueStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(588);
    match(SolidityParser::ContinueKeyword);
    setState(589);
    match(SolidityParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BreakStatementContext ------------------------------------------------------------------

SolidityParser::BreakStatementContext::BreakStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SolidityParser::BreakStatementContext::BreakKeyword() {
  return getToken(SolidityParser::BreakKeyword, 0);
}


size_t SolidityParser::BreakStatementContext::getRuleIndex() const {
  return SolidityParser::RuleBreakStatement;
}


antlrcpp::Any SolidityParser::BreakStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitBreakStatement(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::BreakStatementContext* SolidityParser::breakStatement() {
  BreakStatementContext *_localctx = _tracker.createInstance<BreakStatementContext>(_ctx, getState());
  enterRule(_localctx, 94, SolidityParser::RuleBreakStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(591);
    match(SolidityParser::BreakKeyword);
    setState(592);
    match(SolidityParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ReturnStatementContext ------------------------------------------------------------------

SolidityParser::ReturnStatementContext::ReturnStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SolidityParser::ExpressionContext* SolidityParser::ReturnStatementContext::expression() {
  return getRuleContext<SolidityParser::ExpressionContext>(0);
}


size_t SolidityParser::ReturnStatementContext::getRuleIndex() const {
  return SolidityParser::RuleReturnStatement;
}


antlrcpp::Any SolidityParser::ReturnStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitReturnStatement(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::ReturnStatementContext* SolidityParser::returnStatement() {
  ReturnStatementContext *_localctx = _tracker.createInstance<ReturnStatementContext>(_ctx, getState());
  enterRule(_localctx, 96, SolidityParser::RuleReturnStatement);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(594);
    match(SolidityParser::T__45);
    setState(596);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SolidityParser::T__3)
      | (1ULL << SolidityParser::T__12)
      | (1ULL << SolidityParser::T__20)
      | (1ULL << SolidityParser::T__31)
      | (1ULL << SolidityParser::T__33)
      | (1ULL << SolidityParser::T__39)
      | (1ULL << SolidityParser::T__48)
      | (1ULL << SolidityParser::T__49)
      | (1ULL << SolidityParser::T__50)
      | (1ULL << SolidityParser::T__51)
      | (1ULL << SolidityParser::T__52)
      | (1ULL << SolidityParser::T__53)
      | (1ULL << SolidityParser::T__54)
      | (1ULL << SolidityParser::T__55)
      | (1ULL << SolidityParser::T__56)
      | (1ULL << SolidityParser::T__57)
      | (1ULL << SolidityParser::T__58)
      | (1ULL << SolidityParser::T__59))) != 0) || ((((_la - 91) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 91)) & ((1ULL << (SolidityParser::Int - 91))
      | (1ULL << (SolidityParser::Uint - 91))
      | (1ULL << (SolidityParser::Byte - 91))
      | (1ULL << (SolidityParser::Fixed - 91))
      | (1ULL << (SolidityParser::Ufixed - 91))
      | (1ULL << (SolidityParser::BooleanLiteral - 91))
      | (1ULL << (SolidityParser::DecimalNumber - 91))
      | (1ULL << (SolidityParser::HexNumber - 91))
      | (1ULL << (SolidityParser::HexLiteral - 91))
      | (1ULL << (SolidityParser::Identifier - 91))
      | (1ULL << (SolidityParser::StringLiteral - 91)))) != 0)) {
      setState(595);
      expression(0);
    }
    setState(598);
    match(SolidityParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ThrowStatementContext ------------------------------------------------------------------

SolidityParser::ThrowStatementContext::ThrowStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SolidityParser::ThrowStatementContext::getRuleIndex() const {
  return SolidityParser::RuleThrowStatement;
}


antlrcpp::Any SolidityParser::ThrowStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitThrowStatement(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::ThrowStatementContext* SolidityParser::throwStatement() {
  ThrowStatementContext *_localctx = _tracker.createInstance<ThrowStatementContext>(_ctx, getState());
  enterRule(_localctx, 98, SolidityParser::RuleThrowStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(600);
    match(SolidityParser::T__46);
    setState(601);
    match(SolidityParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EmitStatementContext ------------------------------------------------------------------

SolidityParser::EmitStatementContext::EmitStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SolidityParser::FunctionCallContext* SolidityParser::EmitStatementContext::functionCall() {
  return getRuleContext<SolidityParser::FunctionCallContext>(0);
}


size_t SolidityParser::EmitStatementContext::getRuleIndex() const {
  return SolidityParser::RuleEmitStatement;
}


antlrcpp::Any SolidityParser::EmitStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitEmitStatement(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::EmitStatementContext* SolidityParser::emitStatement() {
  EmitStatementContext *_localctx = _tracker.createInstance<EmitStatementContext>(_ctx, getState());
  enterRule(_localctx, 100, SolidityParser::RuleEmitStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(603);
    match(SolidityParser::T__47);
    setState(604);
    functionCall();
    setState(605);
    match(SolidityParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableDeclarationStatementContext ------------------------------------------------------------------

SolidityParser::VariableDeclarationStatementContext::VariableDeclarationStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SolidityParser::IdentifierListContext* SolidityParser::VariableDeclarationStatementContext::identifierList() {
  return getRuleContext<SolidityParser::IdentifierListContext>(0);
}

SolidityParser::VariableDeclarationContext* SolidityParser::VariableDeclarationStatementContext::variableDeclaration() {
  return getRuleContext<SolidityParser::VariableDeclarationContext>(0);
}

SolidityParser::VariableDeclarationListContext* SolidityParser::VariableDeclarationStatementContext::variableDeclarationList() {
  return getRuleContext<SolidityParser::VariableDeclarationListContext>(0);
}

SolidityParser::ExpressionContext* SolidityParser::VariableDeclarationStatementContext::expression() {
  return getRuleContext<SolidityParser::ExpressionContext>(0);
}


size_t SolidityParser::VariableDeclarationStatementContext::getRuleIndex() const {
  return SolidityParser::RuleVariableDeclarationStatement;
}


antlrcpp::Any SolidityParser::VariableDeclarationStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitVariableDeclarationStatement(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::VariableDeclarationStatementContext* SolidityParser::variableDeclarationStatement() {
  VariableDeclarationStatementContext *_localctx = _tracker.createInstance<VariableDeclarationStatementContext>(_ctx, getState());
  enterRule(_localctx, 102, SolidityParser::RuleVariableDeclarationStatement);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(614);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 61, _ctx)) {
    case 1: {
      setState(607);
      match(SolidityParser::T__48);
      setState(608);
      identifierList();
      break;
    }

    case 2: {
      setState(609);
      variableDeclaration();
      break;
    }

    case 3: {
      setState(610);
      match(SolidityParser::T__20);
      setState(611);
      variableDeclarationList();
      setState(612);
      match(SolidityParser::T__21);
      break;
    }

    }
    setState(618);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SolidityParser::T__8) {
      setState(616);
      match(SolidityParser::T__8);
      setState(617);
      expression(0);
    }
    setState(620);
    match(SolidityParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableDeclarationListContext ------------------------------------------------------------------

SolidityParser::VariableDeclarationListContext::VariableDeclarationListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SolidityParser::VariableDeclarationContext *> SolidityParser::VariableDeclarationListContext::variableDeclaration() {
  return getRuleContexts<SolidityParser::VariableDeclarationContext>();
}

SolidityParser::VariableDeclarationContext* SolidityParser::VariableDeclarationListContext::variableDeclaration(size_t i) {
  return getRuleContext<SolidityParser::VariableDeclarationContext>(i);
}


size_t SolidityParser::VariableDeclarationListContext::getRuleIndex() const {
  return SolidityParser::RuleVariableDeclarationList;
}


antlrcpp::Any SolidityParser::VariableDeclarationListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitVariableDeclarationList(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::VariableDeclarationListContext* SolidityParser::variableDeclarationList() {
  VariableDeclarationListContext *_localctx = _tracker.createInstance<VariableDeclarationListContext>(_ctx, getState());
  enterRule(_localctx, 104, SolidityParser::RuleVariableDeclarationList);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(623);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SolidityParser::T__12)
      | (1ULL << SolidityParser::T__27)
      | (1ULL << SolidityParser::T__33)
      | (1ULL << SolidityParser::T__35)
      | (1ULL << SolidityParser::T__39)
      | (1ULL << SolidityParser::T__48)
      | (1ULL << SolidityParser::T__49)
      | (1ULL << SolidityParser::T__50)
      | (1ULL << SolidityParser::T__51))) != 0) || ((((_la - 91) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 91)) & ((1ULL << (SolidityParser::Int - 91))
      | (1ULL << (SolidityParser::Uint - 91))
      | (1ULL << (SolidityParser::Byte - 91))
      | (1ULL << (SolidityParser::Fixed - 91))
      | (1ULL << (SolidityParser::Ufixed - 91))
      | (1ULL << (SolidityParser::Identifier - 91)))) != 0)) {
      setState(622);
      variableDeclaration();
    }
    setState(631);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SolidityParser::T__14) {
      setState(625);
      match(SolidityParser::T__14);
      setState(627);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << SolidityParser::T__12)
        | (1ULL << SolidityParser::T__27)
        | (1ULL << SolidityParser::T__33)
        | (1ULL << SolidityParser::T__35)
        | (1ULL << SolidityParser::T__39)
        | (1ULL << SolidityParser::T__48)
        | (1ULL << SolidityParser::T__49)
        | (1ULL << SolidityParser::T__50)
        | (1ULL << SolidityParser::T__51))) != 0) || ((((_la - 91) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 91)) & ((1ULL << (SolidityParser::Int - 91))
        | (1ULL << (SolidityParser::Uint - 91))
        | (1ULL << (SolidityParser::Byte - 91))
        | (1ULL << (SolidityParser::Fixed - 91))
        | (1ULL << (SolidityParser::Ufixed - 91))
        | (1ULL << (SolidityParser::Identifier - 91)))) != 0)) {
        setState(626);
        variableDeclaration();
      }
      setState(633);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IdentifierListContext ------------------------------------------------------------------

SolidityParser::IdentifierListContext::IdentifierListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SolidityParser::IdentifierContext *> SolidityParser::IdentifierListContext::identifier() {
  return getRuleContexts<SolidityParser::IdentifierContext>();
}

SolidityParser::IdentifierContext* SolidityParser::IdentifierListContext::identifier(size_t i) {
  return getRuleContext<SolidityParser::IdentifierContext>(i);
}


size_t SolidityParser::IdentifierListContext::getRuleIndex() const {
  return SolidityParser::RuleIdentifierList;
}


antlrcpp::Any SolidityParser::IdentifierListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitIdentifierList(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::IdentifierListContext* SolidityParser::identifierList() {
  IdentifierListContext *_localctx = _tracker.createInstance<IdentifierListContext>(_ctx, getState());
  enterRule(_localctx, 106, SolidityParser::RuleIdentifierList);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(634);
    match(SolidityParser::T__20);
    setState(641);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 67, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(636);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == SolidityParser::T__12

        || _la == SolidityParser::T__39 || _la == SolidityParser::Identifier) {
          setState(635);
          identifier();
        }
        setState(638);
        match(SolidityParser::T__14); 
      }
      setState(643);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 67, _ctx);
    }
    setState(645);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SolidityParser::T__12

    || _la == SolidityParser::T__39 || _la == SolidityParser::Identifier) {
      setState(644);
      identifier();
    }
    setState(647);
    match(SolidityParser::T__21);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ElementaryTypeNameContext ------------------------------------------------------------------

SolidityParser::ElementaryTypeNameContext::ElementaryTypeNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SolidityParser::ElementaryTypeNameContext::Int() {
  return getToken(SolidityParser::Int, 0);
}

tree::TerminalNode* SolidityParser::ElementaryTypeNameContext::Uint() {
  return getToken(SolidityParser::Uint, 0);
}

tree::TerminalNode* SolidityParser::ElementaryTypeNameContext::Byte() {
  return getToken(SolidityParser::Byte, 0);
}

tree::TerminalNode* SolidityParser::ElementaryTypeNameContext::Fixed() {
  return getToken(SolidityParser::Fixed, 0);
}

tree::TerminalNode* SolidityParser::ElementaryTypeNameContext::Ufixed() {
  return getToken(SolidityParser::Ufixed, 0);
}


size_t SolidityParser::ElementaryTypeNameContext::getRuleIndex() const {
  return SolidityParser::RuleElementaryTypeName;
}


antlrcpp::Any SolidityParser::ElementaryTypeNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitElementaryTypeName(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::ElementaryTypeNameContext* SolidityParser::elementaryTypeName() {
  ElementaryTypeNameContext *_localctx = _tracker.createInstance<ElementaryTypeNameContext>(_ctx, getState());
  enterRule(_localctx, 108, SolidityParser::RuleElementaryTypeName);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(649);
    _la = _input->LA(1);
    if (!(((((_la - 34) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 34)) & ((1ULL << (SolidityParser::T__33 - 34))
      | (1ULL << (SolidityParser::T__48 - 34))
      | (1ULL << (SolidityParser::T__49 - 34))
      | (1ULL << (SolidityParser::T__50 - 34))
      | (1ULL << (SolidityParser::T__51 - 34))
      | (1ULL << (SolidityParser::Int - 34))
      | (1ULL << (SolidityParser::Uint - 34))
      | (1ULL << (SolidityParser::Byte - 34))
      | (1ULL << (SolidityParser::Fixed - 34))
      | (1ULL << (SolidityParser::Ufixed - 34)))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionContext ------------------------------------------------------------------

SolidityParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SolidityParser::TypeNameContext* SolidityParser::ExpressionContext::typeName() {
  return getRuleContext<SolidityParser::TypeNameContext>(0);
}

std::vector<SolidityParser::ExpressionContext *> SolidityParser::ExpressionContext::expression() {
  return getRuleContexts<SolidityParser::ExpressionContext>();
}

SolidityParser::ExpressionContext* SolidityParser::ExpressionContext::expression(size_t i) {
  return getRuleContext<SolidityParser::ExpressionContext>(i);
}

SolidityParser::PrimaryExpressionContext* SolidityParser::ExpressionContext::primaryExpression() {
  return getRuleContext<SolidityParser::PrimaryExpressionContext>(0);
}

SolidityParser::FunctionCallArgumentsContext* SolidityParser::ExpressionContext::functionCallArguments() {
  return getRuleContext<SolidityParser::FunctionCallArgumentsContext>(0);
}

SolidityParser::IdentifierContext* SolidityParser::ExpressionContext::identifier() {
  return getRuleContext<SolidityParser::IdentifierContext>(0);
}


size_t SolidityParser::ExpressionContext::getRuleIndex() const {
  return SolidityParser::RuleExpression;
}


antlrcpp::Any SolidityParser::ExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitExpression(this);
  else
    return visitor->visitChildren(this);
}


SolidityParser::ExpressionContext* SolidityParser::expression() {
   return expression(0);
}

SolidityParser::ExpressionContext* SolidityParser::expression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  SolidityParser::ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, parentState);
  SolidityParser::ExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 110;
  enterRecursionRule(_localctx, 110, SolidityParser::RuleExpression, precedence);

    size_t _la = 0;

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(669);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 69, _ctx)) {
    case 1: {
      setState(652);
      match(SolidityParser::T__54);
      setState(653);
      typeName(0);
      break;
    }

    case 2: {
      setState(654);
      match(SolidityParser::T__20);
      setState(655);
      expression(0);
      setState(656);
      match(SolidityParser::T__21);
      break;
    }

    case 3: {
      setState(658);
      _la = _input->LA(1);
      if (!(_la == SolidityParser::T__52

      || _la == SolidityParser::T__53)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(659);
      expression(19);
      break;
    }

    case 4: {
      setState(660);
      _la = _input->LA(1);
      if (!(_la == SolidityParser::T__55

      || _la == SolidityParser::T__56)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(661);
      expression(18);
      break;
    }

    case 5: {
      setState(662);
      _la = _input->LA(1);
      if (!(_la == SolidityParser::T__57

      || _la == SolidityParser::T__58)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(663);
      expression(17);
      break;
    }

    case 6: {
      setState(664);
      match(SolidityParser::T__59);
      setState(665);
      expression(16);
      break;
    }

    case 7: {
      setState(666);
      match(SolidityParser::T__3);
      setState(667);
      expression(15);
      break;
    }

    case 8: {
      setState(668);
      primaryExpression();
      break;
    }

    }
    _ctx->stop = _input->LT(-1);
    setState(730);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 71, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(728);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 70, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(671);

          if (!(precpred(_ctx, 14))) throw FailedPredicateException(this, "precpred(_ctx, 14)");
          setState(672);
          match(SolidityParser::T__60);
          setState(673);
          expression(15);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(674);

          if (!(precpred(_ctx, 13))) throw FailedPredicateException(this, "precpred(_ctx, 13)");
          setState(675);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & ((1ULL << SolidityParser::T__11)
            | (1ULL << SolidityParser::T__61)
            | (1ULL << SolidityParser::T__62))) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(676);
          expression(14);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(677);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(678);
          _la = _input->LA(1);
          if (!(_la == SolidityParser::T__55

          || _la == SolidityParser::T__56)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(679);
          expression(13);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(680);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(681);
          _la = _input->LA(1);
          if (!(_la == SolidityParser::T__63

          || _la == SolidityParser::T__64)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(682);
          expression(12);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(683);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(684);
          match(SolidityParser::T__65);
          setState(685);
          expression(11);
          break;
        }

        case 6: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(686);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(687);
          match(SolidityParser::T__2);
          setState(688);
          expression(10);
          break;
        }

        case 7: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(689);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(690);
          match(SolidityParser::T__66);
          setState(691);
          expression(9);
          break;
        }

        case 8: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(692);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(693);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & ((1ULL << SolidityParser::T__4)
            | (1ULL << SolidityParser::T__5)
            | (1ULL << SolidityParser::T__6)
            | (1ULL << SolidityParser::T__7))) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(694);
          expression(8);
          break;
        }

        case 9: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(695);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(696);
          _la = _input->LA(1);
          if (!(_la == SolidityParser::T__67

          || _la == SolidityParser::T__68)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(697);
          expression(7);
          break;
        }

        case 10: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(698);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(699);
          match(SolidityParser::T__69);
          setState(700);
          expression(6);
          break;
        }

        case 11: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(701);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(702);
          match(SolidityParser::T__70);
          setState(703);
          expression(5);
          break;
        }

        case 12: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(704);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(705);
          match(SolidityParser::T__71);
          setState(706);
          expression(0);
          setState(707);
          match(SolidityParser::T__72);
          setState(708);
          expression(4);
          break;
        }

        case 13: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(710);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(711);
          _la = _input->LA(1);
          if (!(_la == SolidityParser::T__8 || ((((_la - 74) & ~ 0x3fULL) == 0) &&
            ((1ULL << (_la - 74)) & ((1ULL << (SolidityParser::T__73 - 74))
            | (1ULL << (SolidityParser::T__74 - 74))
            | (1ULL << (SolidityParser::T__75 - 74))
            | (1ULL << (SolidityParser::T__76 - 74))
            | (1ULL << (SolidityParser::T__77 - 74))
            | (1ULL << (SolidityParser::T__78 - 74))
            | (1ULL << (SolidityParser::T__79 - 74))
            | (1ULL << (SolidityParser::T__80 - 74))
            | (1ULL << (SolidityParser::T__81 - 74))
            | (1ULL << (SolidityParser::T__82 - 74)))) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(712);
          expression(3);
          break;
        }

        case 14: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(713);

          if (!(precpred(_ctx, 25))) throw FailedPredicateException(this, "precpred(_ctx, 25)");
          setState(714);
          _la = _input->LA(1);
          if (!(_la == SolidityParser::T__52

          || _la == SolidityParser::T__53)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          break;
        }

        case 15: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(715);

          if (!(precpred(_ctx, 23))) throw FailedPredicateException(this, "precpred(_ctx, 23)");
          setState(716);
          match(SolidityParser::T__31);
          setState(717);
          expression(0);
          setState(718);
          match(SolidityParser::T__32);
          break;
        }

        case 16: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(720);

          if (!(precpred(_ctx, 22))) throw FailedPredicateException(this, "precpred(_ctx, 22)");
          setState(721);
          match(SolidityParser::T__20);
          setState(722);
          functionCallArguments();
          setState(723);
          match(SolidityParser::T__21);
          break;
        }

        case 17: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(725);

          if (!(precpred(_ctx, 21))) throw FailedPredicateException(this, "precpred(_ctx, 21)");
          setState(726);
          match(SolidityParser::T__34);
          setState(727);
          identifier();
          break;
        }

        } 
      }
      setState(732);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 71, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- PrimaryExpressionContext ------------------------------------------------------------------

SolidityParser::PrimaryExpressionContext::PrimaryExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SolidityParser::PrimaryExpressionContext::BooleanLiteral() {
  return getToken(SolidityParser::BooleanLiteral, 0);
}

SolidityParser::NumberLiteralContext* SolidityParser::PrimaryExpressionContext::numberLiteral() {
  return getRuleContext<SolidityParser::NumberLiteralContext>(0);
}

tree::TerminalNode* SolidityParser::PrimaryExpressionContext::HexLiteral() {
  return getToken(SolidityParser::HexLiteral, 0);
}

tree::TerminalNode* SolidityParser::PrimaryExpressionContext::StringLiteral() {
  return getToken(SolidityParser::StringLiteral, 0);
}

SolidityParser::IdentifierContext* SolidityParser::PrimaryExpressionContext::identifier() {
  return getRuleContext<SolidityParser::IdentifierContext>(0);
}

SolidityParser::TupleExpressionContext* SolidityParser::PrimaryExpressionContext::tupleExpression() {
  return getRuleContext<SolidityParser::TupleExpressionContext>(0);
}

SolidityParser::ElementaryTypeNameExpressionContext* SolidityParser::PrimaryExpressionContext::elementaryTypeNameExpression() {
  return getRuleContext<SolidityParser::ElementaryTypeNameExpressionContext>(0);
}


size_t SolidityParser::PrimaryExpressionContext::getRuleIndex() const {
  return SolidityParser::RulePrimaryExpression;
}


antlrcpp::Any SolidityParser::PrimaryExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitPrimaryExpression(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::PrimaryExpressionContext* SolidityParser::primaryExpression() {
  PrimaryExpressionContext *_localctx = _tracker.createInstance<PrimaryExpressionContext>(_ctx, getState());
  enterRule(_localctx, 112, SolidityParser::RulePrimaryExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(748);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SolidityParser::BooleanLiteral: {
        enterOuterAlt(_localctx, 1);
        setState(733);
        match(SolidityParser::BooleanLiteral);
        break;
      }

      case SolidityParser::DecimalNumber:
      case SolidityParser::HexNumber: {
        enterOuterAlt(_localctx, 2);
        setState(734);
        numberLiteral();
        break;
      }

      case SolidityParser::HexLiteral: {
        enterOuterAlt(_localctx, 3);
        setState(735);
        match(SolidityParser::HexLiteral);
        break;
      }

      case SolidityParser::StringLiteral: {
        enterOuterAlt(_localctx, 4);
        setState(736);
        match(SolidityParser::StringLiteral);
        break;
      }

      case SolidityParser::T__12:
      case SolidityParser::T__39:
      case SolidityParser::Identifier: {
        enterOuterAlt(_localctx, 5);
        setState(737);
        identifier();
        setState(740);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 72, _ctx)) {
        case 1: {
          setState(738);
          match(SolidityParser::T__31);
          setState(739);
          match(SolidityParser::T__32);
          break;
        }

        }
        break;
      }

      case SolidityParser::T__20:
      case SolidityParser::T__31: {
        enterOuterAlt(_localctx, 6);
        setState(742);
        tupleExpression();
        break;
      }

      case SolidityParser::T__33:
      case SolidityParser::T__48:
      case SolidityParser::T__49:
      case SolidityParser::T__50:
      case SolidityParser::T__51:
      case SolidityParser::Int:
      case SolidityParser::Uint:
      case SolidityParser::Byte:
      case SolidityParser::Fixed:
      case SolidityParser::Ufixed: {
        enterOuterAlt(_localctx, 7);
        setState(743);
        elementaryTypeNameExpression();
        setState(746);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 73, _ctx)) {
        case 1: {
          setState(744);
          match(SolidityParser::T__31);
          setState(745);
          match(SolidityParser::T__32);
          break;
        }

        }
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionListContext ------------------------------------------------------------------

SolidityParser::ExpressionListContext::ExpressionListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SolidityParser::ExpressionContext *> SolidityParser::ExpressionListContext::expression() {
  return getRuleContexts<SolidityParser::ExpressionContext>();
}

SolidityParser::ExpressionContext* SolidityParser::ExpressionListContext::expression(size_t i) {
  return getRuleContext<SolidityParser::ExpressionContext>(i);
}


size_t SolidityParser::ExpressionListContext::getRuleIndex() const {
  return SolidityParser::RuleExpressionList;
}


antlrcpp::Any SolidityParser::ExpressionListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitExpressionList(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::ExpressionListContext* SolidityParser::expressionList() {
  ExpressionListContext *_localctx = _tracker.createInstance<ExpressionListContext>(_ctx, getState());
  enterRule(_localctx, 114, SolidityParser::RuleExpressionList);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(750);
    expression(0);
    setState(755);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SolidityParser::T__14) {
      setState(751);
      match(SolidityParser::T__14);
      setState(752);
      expression(0);
      setState(757);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NameValueListContext ------------------------------------------------------------------

SolidityParser::NameValueListContext::NameValueListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SolidityParser::NameValueContext *> SolidityParser::NameValueListContext::nameValue() {
  return getRuleContexts<SolidityParser::NameValueContext>();
}

SolidityParser::NameValueContext* SolidityParser::NameValueListContext::nameValue(size_t i) {
  return getRuleContext<SolidityParser::NameValueContext>(i);
}


size_t SolidityParser::NameValueListContext::getRuleIndex() const {
  return SolidityParser::RuleNameValueList;
}


antlrcpp::Any SolidityParser::NameValueListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitNameValueList(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::NameValueListContext* SolidityParser::nameValueList() {
  NameValueListContext *_localctx = _tracker.createInstance<NameValueListContext>(_ctx, getState());
  enterRule(_localctx, 116, SolidityParser::RuleNameValueList);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(758);
    nameValue();
    setState(763);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 76, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(759);
        match(SolidityParser::T__14);
        setState(760);
        nameValue(); 
      }
      setState(765);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 76, _ctx);
    }
    setState(767);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SolidityParser::T__14) {
      setState(766);
      match(SolidityParser::T__14);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NameValueContext ------------------------------------------------------------------

SolidityParser::NameValueContext::NameValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SolidityParser::IdentifierContext* SolidityParser::NameValueContext::identifier() {
  return getRuleContext<SolidityParser::IdentifierContext>(0);
}

SolidityParser::ExpressionContext* SolidityParser::NameValueContext::expression() {
  return getRuleContext<SolidityParser::ExpressionContext>(0);
}


size_t SolidityParser::NameValueContext::getRuleIndex() const {
  return SolidityParser::RuleNameValue;
}


antlrcpp::Any SolidityParser::NameValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitNameValue(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::NameValueContext* SolidityParser::nameValue() {
  NameValueContext *_localctx = _tracker.createInstance<NameValueContext>(_ctx, getState());
  enterRule(_localctx, 118, SolidityParser::RuleNameValue);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(769);
    identifier();
    setState(770);
    match(SolidityParser::T__72);
    setState(771);
    expression(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionCallArgumentsContext ------------------------------------------------------------------

SolidityParser::FunctionCallArgumentsContext::FunctionCallArgumentsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SolidityParser::NameValueListContext* SolidityParser::FunctionCallArgumentsContext::nameValueList() {
  return getRuleContext<SolidityParser::NameValueListContext>(0);
}

SolidityParser::ExpressionListContext* SolidityParser::FunctionCallArgumentsContext::expressionList() {
  return getRuleContext<SolidityParser::ExpressionListContext>(0);
}


size_t SolidityParser::FunctionCallArgumentsContext::getRuleIndex() const {
  return SolidityParser::RuleFunctionCallArguments;
}


antlrcpp::Any SolidityParser::FunctionCallArgumentsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitFunctionCallArguments(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::FunctionCallArgumentsContext* SolidityParser::functionCallArguments() {
  FunctionCallArgumentsContext *_localctx = _tracker.createInstance<FunctionCallArgumentsContext>(_ctx, getState());
  enterRule(_localctx, 120, SolidityParser::RuleFunctionCallArguments);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(781);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SolidityParser::T__13: {
        enterOuterAlt(_localctx, 1);
        setState(773);
        match(SolidityParser::T__13);
        setState(775);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == SolidityParser::T__12

        || _la == SolidityParser::T__39 || _la == SolidityParser::Identifier) {
          setState(774);
          nameValueList();
        }
        setState(777);
        match(SolidityParser::T__15);
        break;
      }

      case SolidityParser::T__3:
      case SolidityParser::T__12:
      case SolidityParser::T__20:
      case SolidityParser::T__21:
      case SolidityParser::T__31:
      case SolidityParser::T__33:
      case SolidityParser::T__39:
      case SolidityParser::T__48:
      case SolidityParser::T__49:
      case SolidityParser::T__50:
      case SolidityParser::T__51:
      case SolidityParser::T__52:
      case SolidityParser::T__53:
      case SolidityParser::T__54:
      case SolidityParser::T__55:
      case SolidityParser::T__56:
      case SolidityParser::T__57:
      case SolidityParser::T__58:
      case SolidityParser::T__59:
      case SolidityParser::Int:
      case SolidityParser::Uint:
      case SolidityParser::Byte:
      case SolidityParser::Fixed:
      case SolidityParser::Ufixed:
      case SolidityParser::BooleanLiteral:
      case SolidityParser::DecimalNumber:
      case SolidityParser::HexNumber:
      case SolidityParser::HexLiteral:
      case SolidityParser::Identifier:
      case SolidityParser::StringLiteral: {
        enterOuterAlt(_localctx, 2);
        setState(779);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << SolidityParser::T__3)
          | (1ULL << SolidityParser::T__12)
          | (1ULL << SolidityParser::T__20)
          | (1ULL << SolidityParser::T__31)
          | (1ULL << SolidityParser::T__33)
          | (1ULL << SolidityParser::T__39)
          | (1ULL << SolidityParser::T__48)
          | (1ULL << SolidityParser::T__49)
          | (1ULL << SolidityParser::T__50)
          | (1ULL << SolidityParser::T__51)
          | (1ULL << SolidityParser::T__52)
          | (1ULL << SolidityParser::T__53)
          | (1ULL << SolidityParser::T__54)
          | (1ULL << SolidityParser::T__55)
          | (1ULL << SolidityParser::T__56)
          | (1ULL << SolidityParser::T__57)
          | (1ULL << SolidityParser::T__58)
          | (1ULL << SolidityParser::T__59))) != 0) || ((((_la - 91) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 91)) & ((1ULL << (SolidityParser::Int - 91))
          | (1ULL << (SolidityParser::Uint - 91))
          | (1ULL << (SolidityParser::Byte - 91))
          | (1ULL << (SolidityParser::Fixed - 91))
          | (1ULL << (SolidityParser::Ufixed - 91))
          | (1ULL << (SolidityParser::BooleanLiteral - 91))
          | (1ULL << (SolidityParser::DecimalNumber - 91))
          | (1ULL << (SolidityParser::HexNumber - 91))
          | (1ULL << (SolidityParser::HexLiteral - 91))
          | (1ULL << (SolidityParser::Identifier - 91))
          | (1ULL << (SolidityParser::StringLiteral - 91)))) != 0)) {
          setState(778);
          expressionList();
        }
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionCallContext ------------------------------------------------------------------

SolidityParser::FunctionCallContext::FunctionCallContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SolidityParser::ExpressionContext* SolidityParser::FunctionCallContext::expression() {
  return getRuleContext<SolidityParser::ExpressionContext>(0);
}

SolidityParser::FunctionCallArgumentsContext* SolidityParser::FunctionCallContext::functionCallArguments() {
  return getRuleContext<SolidityParser::FunctionCallArgumentsContext>(0);
}


size_t SolidityParser::FunctionCallContext::getRuleIndex() const {
  return SolidityParser::RuleFunctionCall;
}


antlrcpp::Any SolidityParser::FunctionCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitFunctionCall(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::FunctionCallContext* SolidityParser::functionCall() {
  FunctionCallContext *_localctx = _tracker.createInstance<FunctionCallContext>(_ctx, getState());
  enterRule(_localctx, 122, SolidityParser::RuleFunctionCall);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(783);
    expression(0);
    setState(784);
    match(SolidityParser::T__20);
    setState(785);
    functionCallArguments();
    setState(786);
    match(SolidityParser::T__21);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssemblyBlockContext ------------------------------------------------------------------

SolidityParser::AssemblyBlockContext::AssemblyBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SolidityParser::AssemblyItemContext *> SolidityParser::AssemblyBlockContext::assemblyItem() {
  return getRuleContexts<SolidityParser::AssemblyItemContext>();
}

SolidityParser::AssemblyItemContext* SolidityParser::AssemblyBlockContext::assemblyItem(size_t i) {
  return getRuleContext<SolidityParser::AssemblyItemContext>(i);
}


size_t SolidityParser::AssemblyBlockContext::getRuleIndex() const {
  return SolidityParser::RuleAssemblyBlock;
}


antlrcpp::Any SolidityParser::AssemblyBlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitAssemblyBlock(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::AssemblyBlockContext* SolidityParser::assemblyBlock() {
  AssemblyBlockContext *_localctx = _tracker.createInstance<AssemblyBlockContext>(_ctx, getState());
  enterRule(_localctx, 124, SolidityParser::RuleAssemblyBlock);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(788);
    match(SolidityParser::T__13);
    setState(792);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SolidityParser::T__12)
      | (1ULL << SolidityParser::T__13)
      | (1ULL << SolidityParser::T__20)
      | (1ULL << SolidityParser::T__23)
      | (1ULL << SolidityParser::T__27)
      | (1ULL << SolidityParser::T__33)
      | (1ULL << SolidityParser::T__39)
      | (1ULL << SolidityParser::T__40)
      | (1ULL << SolidityParser::T__43)
      | (1ULL << SolidityParser::T__45)
      | (1ULL << SolidityParser::T__51))) != 0) || ((((_la - 84) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 84)) & ((1ULL << (SolidityParser::T__83 - 84))
      | (1ULL << (SolidityParser::T__85 - 84))
      | (1ULL << (SolidityParser::T__86 - 84))
      | (1ULL << (SolidityParser::DecimalNumber - 84))
      | (1ULL << (SolidityParser::HexNumber - 84))
      | (1ULL << (SolidityParser::HexLiteral - 84))
      | (1ULL << (SolidityParser::BreakKeyword - 84))
      | (1ULL << (SolidityParser::ContinueKeyword - 84))
      | (1ULL << (SolidityParser::Identifier - 84))
      | (1ULL << (SolidityParser::StringLiteral - 84)))) != 0)) {
      setState(789);
      assemblyItem();
      setState(794);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(795);
    match(SolidityParser::T__15);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssemblyItemContext ------------------------------------------------------------------

SolidityParser::AssemblyItemContext::AssemblyItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SolidityParser::IdentifierContext* SolidityParser::AssemblyItemContext::identifier() {
  return getRuleContext<SolidityParser::IdentifierContext>(0);
}

SolidityParser::AssemblyBlockContext* SolidityParser::AssemblyItemContext::assemblyBlock() {
  return getRuleContext<SolidityParser::AssemblyBlockContext>(0);
}

SolidityParser::AssemblyExpressionContext* SolidityParser::AssemblyItemContext::assemblyExpression() {
  return getRuleContext<SolidityParser::AssemblyExpressionContext>(0);
}

SolidityParser::AssemblyLocalDefinitionContext* SolidityParser::AssemblyItemContext::assemblyLocalDefinition() {
  return getRuleContext<SolidityParser::AssemblyLocalDefinitionContext>(0);
}

SolidityParser::AssemblyAssignmentContext* SolidityParser::AssemblyItemContext::assemblyAssignment() {
  return getRuleContext<SolidityParser::AssemblyAssignmentContext>(0);
}

SolidityParser::AssemblyStackAssignmentContext* SolidityParser::AssemblyItemContext::assemblyStackAssignment() {
  return getRuleContext<SolidityParser::AssemblyStackAssignmentContext>(0);
}

SolidityParser::LabelDefinitionContext* SolidityParser::AssemblyItemContext::labelDefinition() {
  return getRuleContext<SolidityParser::LabelDefinitionContext>(0);
}

SolidityParser::AssemblySwitchContext* SolidityParser::AssemblyItemContext::assemblySwitch() {
  return getRuleContext<SolidityParser::AssemblySwitchContext>(0);
}

SolidityParser::AssemblyFunctionDefinitionContext* SolidityParser::AssemblyItemContext::assemblyFunctionDefinition() {
  return getRuleContext<SolidityParser::AssemblyFunctionDefinitionContext>(0);
}

SolidityParser::AssemblyForContext* SolidityParser::AssemblyItemContext::assemblyFor() {
  return getRuleContext<SolidityParser::AssemblyForContext>(0);
}

SolidityParser::AssemblyIfContext* SolidityParser::AssemblyItemContext::assemblyIf() {
  return getRuleContext<SolidityParser::AssemblyIfContext>(0);
}

tree::TerminalNode* SolidityParser::AssemblyItemContext::BreakKeyword() {
  return getToken(SolidityParser::BreakKeyword, 0);
}

tree::TerminalNode* SolidityParser::AssemblyItemContext::ContinueKeyword() {
  return getToken(SolidityParser::ContinueKeyword, 0);
}

SolidityParser::SubAssemblyContext* SolidityParser::AssemblyItemContext::subAssembly() {
  return getRuleContext<SolidityParser::SubAssemblyContext>(0);
}

SolidityParser::NumberLiteralContext* SolidityParser::AssemblyItemContext::numberLiteral() {
  return getRuleContext<SolidityParser::NumberLiteralContext>(0);
}

tree::TerminalNode* SolidityParser::AssemblyItemContext::StringLiteral() {
  return getToken(SolidityParser::StringLiteral, 0);
}

tree::TerminalNode* SolidityParser::AssemblyItemContext::HexLiteral() {
  return getToken(SolidityParser::HexLiteral, 0);
}


size_t SolidityParser::AssemblyItemContext::getRuleIndex() const {
  return SolidityParser::RuleAssemblyItem;
}


antlrcpp::Any SolidityParser::AssemblyItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitAssemblyItem(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::AssemblyItemContext* SolidityParser::assemblyItem() {
  AssemblyItemContext *_localctx = _tracker.createInstance<AssemblyItemContext>(_ctx, getState());
  enterRule(_localctx, 126, SolidityParser::RuleAssemblyItem);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(814);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 82, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(797);
      identifier();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(798);
      assemblyBlock();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(799);
      assemblyExpression();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(800);
      assemblyLocalDefinition();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(801);
      assemblyAssignment();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(802);
      assemblyStackAssignment();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(803);
      labelDefinition();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(804);
      assemblySwitch();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(805);
      assemblyFunctionDefinition();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(806);
      assemblyFor();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(807);
      assemblyIf();
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(808);
      match(SolidityParser::BreakKeyword);
      break;
    }

    case 13: {
      enterOuterAlt(_localctx, 13);
      setState(809);
      match(SolidityParser::ContinueKeyword);
      break;
    }

    case 14: {
      enterOuterAlt(_localctx, 14);
      setState(810);
      subAssembly();
      break;
    }

    case 15: {
      enterOuterAlt(_localctx, 15);
      setState(811);
      numberLiteral();
      break;
    }

    case 16: {
      enterOuterAlt(_localctx, 16);
      setState(812);
      match(SolidityParser::StringLiteral);
      break;
    }

    case 17: {
      enterOuterAlt(_localctx, 17);
      setState(813);
      match(SolidityParser::HexLiteral);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssemblyExpressionContext ------------------------------------------------------------------

SolidityParser::AssemblyExpressionContext::AssemblyExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SolidityParser::AssemblyCallContext* SolidityParser::AssemblyExpressionContext::assemblyCall() {
  return getRuleContext<SolidityParser::AssemblyCallContext>(0);
}

SolidityParser::AssemblyLiteralContext* SolidityParser::AssemblyExpressionContext::assemblyLiteral() {
  return getRuleContext<SolidityParser::AssemblyLiteralContext>(0);
}


size_t SolidityParser::AssemblyExpressionContext::getRuleIndex() const {
  return SolidityParser::RuleAssemblyExpression;
}


antlrcpp::Any SolidityParser::AssemblyExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitAssemblyExpression(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::AssemblyExpressionContext* SolidityParser::assemblyExpression() {
  AssemblyExpressionContext *_localctx = _tracker.createInstance<AssemblyExpressionContext>(_ctx, getState());
  enterRule(_localctx, 128, SolidityParser::RuleAssemblyExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(818);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SolidityParser::T__12:
      case SolidityParser::T__33:
      case SolidityParser::T__39:
      case SolidityParser::T__45:
      case SolidityParser::T__51:
      case SolidityParser::Identifier: {
        enterOuterAlt(_localctx, 1);
        setState(816);
        assemblyCall();
        break;
      }

      case SolidityParser::DecimalNumber:
      case SolidityParser::HexNumber:
      case SolidityParser::HexLiteral:
      case SolidityParser::StringLiteral: {
        enterOuterAlt(_localctx, 2);
        setState(817);
        assemblyLiteral();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssemblyCallContext ------------------------------------------------------------------

SolidityParser::AssemblyCallContext::AssemblyCallContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SolidityParser::IdentifierContext* SolidityParser::AssemblyCallContext::identifier() {
  return getRuleContext<SolidityParser::IdentifierContext>(0);
}

std::vector<SolidityParser::AssemblyExpressionContext *> SolidityParser::AssemblyCallContext::assemblyExpression() {
  return getRuleContexts<SolidityParser::AssemblyExpressionContext>();
}

SolidityParser::AssemblyExpressionContext* SolidityParser::AssemblyCallContext::assemblyExpression(size_t i) {
  return getRuleContext<SolidityParser::AssemblyExpressionContext>(i);
}


size_t SolidityParser::AssemblyCallContext::getRuleIndex() const {
  return SolidityParser::RuleAssemblyCall;
}


antlrcpp::Any SolidityParser::AssemblyCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitAssemblyCall(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::AssemblyCallContext* SolidityParser::assemblyCall() {
  AssemblyCallContext *_localctx = _tracker.createInstance<AssemblyCallContext>(_ctx, getState());
  enterRule(_localctx, 130, SolidityParser::RuleAssemblyCall);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(824);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SolidityParser::T__45: {
        setState(820);
        match(SolidityParser::T__45);
        break;
      }

      case SolidityParser::T__33: {
        setState(821);
        match(SolidityParser::T__33);
        break;
      }

      case SolidityParser::T__51: {
        setState(822);
        match(SolidityParser::T__51);
        break;
      }

      case SolidityParser::T__12:
      case SolidityParser::T__39:
      case SolidityParser::Identifier: {
        setState(823);
        identifier();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(838);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 87, _ctx)) {
    case 1: {
      setState(826);
      match(SolidityParser::T__20);
      setState(828);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << SolidityParser::T__12)
        | (1ULL << SolidityParser::T__33)
        | (1ULL << SolidityParser::T__39)
        | (1ULL << SolidityParser::T__45)
        | (1ULL << SolidityParser::T__51))) != 0) || ((((_la - 98) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 98)) & ((1ULL << (SolidityParser::DecimalNumber - 98))
        | (1ULL << (SolidityParser::HexNumber - 98))
        | (1ULL << (SolidityParser::HexLiteral - 98))
        | (1ULL << (SolidityParser::Identifier - 98))
        | (1ULL << (SolidityParser::StringLiteral - 98)))) != 0)) {
        setState(827);
        assemblyExpression();
      }
      setState(834);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == SolidityParser::T__14) {
        setState(830);
        match(SolidityParser::T__14);
        setState(831);
        assemblyExpression();
        setState(836);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(837);
      match(SolidityParser::T__21);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssemblyLocalDefinitionContext ------------------------------------------------------------------

SolidityParser::AssemblyLocalDefinitionContext::AssemblyLocalDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SolidityParser::AssemblyIdentifierOrListContext* SolidityParser::AssemblyLocalDefinitionContext::assemblyIdentifierOrList() {
  return getRuleContext<SolidityParser::AssemblyIdentifierOrListContext>(0);
}

SolidityParser::AssemblyExpressionContext* SolidityParser::AssemblyLocalDefinitionContext::assemblyExpression() {
  return getRuleContext<SolidityParser::AssemblyExpressionContext>(0);
}


size_t SolidityParser::AssemblyLocalDefinitionContext::getRuleIndex() const {
  return SolidityParser::RuleAssemblyLocalDefinition;
}


antlrcpp::Any SolidityParser::AssemblyLocalDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitAssemblyLocalDefinition(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::AssemblyLocalDefinitionContext* SolidityParser::assemblyLocalDefinition() {
  AssemblyLocalDefinitionContext *_localctx = _tracker.createInstance<AssemblyLocalDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 132, SolidityParser::RuleAssemblyLocalDefinition);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(840);
    match(SolidityParser::T__83);
    setState(841);
    assemblyIdentifierOrList();
    setState(844);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SolidityParser::T__84) {
      setState(842);
      match(SolidityParser::T__84);
      setState(843);
      assemblyExpression();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssemblyAssignmentContext ------------------------------------------------------------------

SolidityParser::AssemblyAssignmentContext::AssemblyAssignmentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SolidityParser::AssemblyIdentifierOrListContext* SolidityParser::AssemblyAssignmentContext::assemblyIdentifierOrList() {
  return getRuleContext<SolidityParser::AssemblyIdentifierOrListContext>(0);
}

SolidityParser::AssemblyExpressionContext* SolidityParser::AssemblyAssignmentContext::assemblyExpression() {
  return getRuleContext<SolidityParser::AssemblyExpressionContext>(0);
}


size_t SolidityParser::AssemblyAssignmentContext::getRuleIndex() const {
  return SolidityParser::RuleAssemblyAssignment;
}


antlrcpp::Any SolidityParser::AssemblyAssignmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitAssemblyAssignment(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::AssemblyAssignmentContext* SolidityParser::assemblyAssignment() {
  AssemblyAssignmentContext *_localctx = _tracker.createInstance<AssemblyAssignmentContext>(_ctx, getState());
  enterRule(_localctx, 134, SolidityParser::RuleAssemblyAssignment);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(846);
    assemblyIdentifierOrList();
    setState(847);
    match(SolidityParser::T__84);
    setState(848);
    assemblyExpression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssemblyIdentifierOrListContext ------------------------------------------------------------------

SolidityParser::AssemblyIdentifierOrListContext::AssemblyIdentifierOrListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SolidityParser::IdentifierContext* SolidityParser::AssemblyIdentifierOrListContext::identifier() {
  return getRuleContext<SolidityParser::IdentifierContext>(0);
}

SolidityParser::AssemblyIdentifierListContext* SolidityParser::AssemblyIdentifierOrListContext::assemblyIdentifierList() {
  return getRuleContext<SolidityParser::AssemblyIdentifierListContext>(0);
}


size_t SolidityParser::AssemblyIdentifierOrListContext::getRuleIndex() const {
  return SolidityParser::RuleAssemblyIdentifierOrList;
}


antlrcpp::Any SolidityParser::AssemblyIdentifierOrListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitAssemblyIdentifierOrList(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::AssemblyIdentifierOrListContext* SolidityParser::assemblyIdentifierOrList() {
  AssemblyIdentifierOrListContext *_localctx = _tracker.createInstance<AssemblyIdentifierOrListContext>(_ctx, getState());
  enterRule(_localctx, 136, SolidityParser::RuleAssemblyIdentifierOrList);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(855);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SolidityParser::T__12:
      case SolidityParser::T__39:
      case SolidityParser::Identifier: {
        enterOuterAlt(_localctx, 1);
        setState(850);
        identifier();
        break;
      }

      case SolidityParser::T__20: {
        enterOuterAlt(_localctx, 2);
        setState(851);
        match(SolidityParser::T__20);
        setState(852);
        assemblyIdentifierList();
        setState(853);
        match(SolidityParser::T__21);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssemblyIdentifierListContext ------------------------------------------------------------------

SolidityParser::AssemblyIdentifierListContext::AssemblyIdentifierListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SolidityParser::IdentifierContext *> SolidityParser::AssemblyIdentifierListContext::identifier() {
  return getRuleContexts<SolidityParser::IdentifierContext>();
}

SolidityParser::IdentifierContext* SolidityParser::AssemblyIdentifierListContext::identifier(size_t i) {
  return getRuleContext<SolidityParser::IdentifierContext>(i);
}


size_t SolidityParser::AssemblyIdentifierListContext::getRuleIndex() const {
  return SolidityParser::RuleAssemblyIdentifierList;
}


antlrcpp::Any SolidityParser::AssemblyIdentifierListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitAssemblyIdentifierList(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::AssemblyIdentifierListContext* SolidityParser::assemblyIdentifierList() {
  AssemblyIdentifierListContext *_localctx = _tracker.createInstance<AssemblyIdentifierListContext>(_ctx, getState());
  enterRule(_localctx, 138, SolidityParser::RuleAssemblyIdentifierList);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(857);
    identifier();
    setState(862);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SolidityParser::T__14) {
      setState(858);
      match(SolidityParser::T__14);
      setState(859);
      identifier();
      setState(864);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssemblyStackAssignmentContext ------------------------------------------------------------------

SolidityParser::AssemblyStackAssignmentContext::AssemblyStackAssignmentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SolidityParser::IdentifierContext* SolidityParser::AssemblyStackAssignmentContext::identifier() {
  return getRuleContext<SolidityParser::IdentifierContext>(0);
}


size_t SolidityParser::AssemblyStackAssignmentContext::getRuleIndex() const {
  return SolidityParser::RuleAssemblyStackAssignment;
}


antlrcpp::Any SolidityParser::AssemblyStackAssignmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitAssemblyStackAssignment(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::AssemblyStackAssignmentContext* SolidityParser::assemblyStackAssignment() {
  AssemblyStackAssignmentContext *_localctx = _tracker.createInstance<AssemblyStackAssignmentContext>(_ctx, getState());
  enterRule(_localctx, 140, SolidityParser::RuleAssemblyStackAssignment);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(865);
    match(SolidityParser::T__85);
    setState(866);
    identifier();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LabelDefinitionContext ------------------------------------------------------------------

SolidityParser::LabelDefinitionContext::LabelDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SolidityParser::IdentifierContext* SolidityParser::LabelDefinitionContext::identifier() {
  return getRuleContext<SolidityParser::IdentifierContext>(0);
}


size_t SolidityParser::LabelDefinitionContext::getRuleIndex() const {
  return SolidityParser::RuleLabelDefinition;
}


antlrcpp::Any SolidityParser::LabelDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitLabelDefinition(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::LabelDefinitionContext* SolidityParser::labelDefinition() {
  LabelDefinitionContext *_localctx = _tracker.createInstance<LabelDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 142, SolidityParser::RuleLabelDefinition);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(868);
    identifier();
    setState(869);
    match(SolidityParser::T__72);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssemblySwitchContext ------------------------------------------------------------------

SolidityParser::AssemblySwitchContext::AssemblySwitchContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SolidityParser::AssemblyExpressionContext* SolidityParser::AssemblySwitchContext::assemblyExpression() {
  return getRuleContext<SolidityParser::AssemblyExpressionContext>(0);
}

std::vector<SolidityParser::AssemblyCaseContext *> SolidityParser::AssemblySwitchContext::assemblyCase() {
  return getRuleContexts<SolidityParser::AssemblyCaseContext>();
}

SolidityParser::AssemblyCaseContext* SolidityParser::AssemblySwitchContext::assemblyCase(size_t i) {
  return getRuleContext<SolidityParser::AssemblyCaseContext>(i);
}


size_t SolidityParser::AssemblySwitchContext::getRuleIndex() const {
  return SolidityParser::RuleAssemblySwitch;
}


antlrcpp::Any SolidityParser::AssemblySwitchContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitAssemblySwitch(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::AssemblySwitchContext* SolidityParser::assemblySwitch() {
  AssemblySwitchContext *_localctx = _tracker.createInstance<AssemblySwitchContext>(_ctx, getState());
  enterRule(_localctx, 144, SolidityParser::RuleAssemblySwitch);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(871);
    match(SolidityParser::T__86);
    setState(872);
    assemblyExpression();
    setState(876);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SolidityParser::T__87

    || _la == SolidityParser::T__88) {
      setState(873);
      assemblyCase();
      setState(878);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssemblyCaseContext ------------------------------------------------------------------

SolidityParser::AssemblyCaseContext::AssemblyCaseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SolidityParser::AssemblyLiteralContext* SolidityParser::AssemblyCaseContext::assemblyLiteral() {
  return getRuleContext<SolidityParser::AssemblyLiteralContext>(0);
}

SolidityParser::AssemblyBlockContext* SolidityParser::AssemblyCaseContext::assemblyBlock() {
  return getRuleContext<SolidityParser::AssemblyBlockContext>(0);
}


size_t SolidityParser::AssemblyCaseContext::getRuleIndex() const {
  return SolidityParser::RuleAssemblyCase;
}


antlrcpp::Any SolidityParser::AssemblyCaseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitAssemblyCase(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::AssemblyCaseContext* SolidityParser::assemblyCase() {
  AssemblyCaseContext *_localctx = _tracker.createInstance<AssemblyCaseContext>(_ctx, getState());
  enterRule(_localctx, 146, SolidityParser::RuleAssemblyCase);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(885);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SolidityParser::T__87: {
        enterOuterAlt(_localctx, 1);
        setState(879);
        match(SolidityParser::T__87);
        setState(880);
        assemblyLiteral();
        setState(881);
        assemblyBlock();
        break;
      }

      case SolidityParser::T__88: {
        enterOuterAlt(_localctx, 2);
        setState(883);
        match(SolidityParser::T__88);
        setState(884);
        assemblyBlock();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssemblyFunctionDefinitionContext ------------------------------------------------------------------

SolidityParser::AssemblyFunctionDefinitionContext::AssemblyFunctionDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SolidityParser::IdentifierContext* SolidityParser::AssemblyFunctionDefinitionContext::identifier() {
  return getRuleContext<SolidityParser::IdentifierContext>(0);
}

SolidityParser::AssemblyBlockContext* SolidityParser::AssemblyFunctionDefinitionContext::assemblyBlock() {
  return getRuleContext<SolidityParser::AssemblyBlockContext>(0);
}

SolidityParser::AssemblyIdentifierListContext* SolidityParser::AssemblyFunctionDefinitionContext::assemblyIdentifierList() {
  return getRuleContext<SolidityParser::AssemblyIdentifierListContext>(0);
}

SolidityParser::AssemblyFunctionReturnsContext* SolidityParser::AssemblyFunctionDefinitionContext::assemblyFunctionReturns() {
  return getRuleContext<SolidityParser::AssemblyFunctionReturnsContext>(0);
}


size_t SolidityParser::AssemblyFunctionDefinitionContext::getRuleIndex() const {
  return SolidityParser::RuleAssemblyFunctionDefinition;
}


antlrcpp::Any SolidityParser::AssemblyFunctionDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitAssemblyFunctionDefinition(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::AssemblyFunctionDefinitionContext* SolidityParser::assemblyFunctionDefinition() {
  AssemblyFunctionDefinitionContext *_localctx = _tracker.createInstance<AssemblyFunctionDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 148, SolidityParser::RuleAssemblyFunctionDefinition);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(887);
    match(SolidityParser::T__27);
    setState(888);
    identifier();
    setState(889);
    match(SolidityParser::T__20);
    setState(891);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SolidityParser::T__12

    || _la == SolidityParser::T__39 || _la == SolidityParser::Identifier) {
      setState(890);
      assemblyIdentifierList();
    }
    setState(893);
    match(SolidityParser::T__21);
    setState(895);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SolidityParser::T__89) {
      setState(894);
      assemblyFunctionReturns();
    }
    setState(897);
    assemblyBlock();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssemblyFunctionReturnsContext ------------------------------------------------------------------

SolidityParser::AssemblyFunctionReturnsContext::AssemblyFunctionReturnsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SolidityParser::AssemblyIdentifierListContext* SolidityParser::AssemblyFunctionReturnsContext::assemblyIdentifierList() {
  return getRuleContext<SolidityParser::AssemblyIdentifierListContext>(0);
}


size_t SolidityParser::AssemblyFunctionReturnsContext::getRuleIndex() const {
  return SolidityParser::RuleAssemblyFunctionReturns;
}


antlrcpp::Any SolidityParser::AssemblyFunctionReturnsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitAssemblyFunctionReturns(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::AssemblyFunctionReturnsContext* SolidityParser::assemblyFunctionReturns() {
  AssemblyFunctionReturnsContext *_localctx = _tracker.createInstance<AssemblyFunctionReturnsContext>(_ctx, getState());
  enterRule(_localctx, 150, SolidityParser::RuleAssemblyFunctionReturns);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(899);
    match(SolidityParser::T__89);
    setState(900);
    assemblyIdentifierList();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssemblyForContext ------------------------------------------------------------------

SolidityParser::AssemblyForContext::AssemblyForContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SolidityParser::AssemblyExpressionContext *> SolidityParser::AssemblyForContext::assemblyExpression() {
  return getRuleContexts<SolidityParser::AssemblyExpressionContext>();
}

SolidityParser::AssemblyExpressionContext* SolidityParser::AssemblyForContext::assemblyExpression(size_t i) {
  return getRuleContext<SolidityParser::AssemblyExpressionContext>(i);
}

std::vector<SolidityParser::AssemblyBlockContext *> SolidityParser::AssemblyForContext::assemblyBlock() {
  return getRuleContexts<SolidityParser::AssemblyBlockContext>();
}

SolidityParser::AssemblyBlockContext* SolidityParser::AssemblyForContext::assemblyBlock(size_t i) {
  return getRuleContext<SolidityParser::AssemblyBlockContext>(i);
}


size_t SolidityParser::AssemblyForContext::getRuleIndex() const {
  return SolidityParser::RuleAssemblyFor;
}


antlrcpp::Any SolidityParser::AssemblyForContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitAssemblyFor(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::AssemblyForContext* SolidityParser::assemblyFor() {
  AssemblyForContext *_localctx = _tracker.createInstance<AssemblyForContext>(_ctx, getState());
  enterRule(_localctx, 152, SolidityParser::RuleAssemblyFor);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(902);
    match(SolidityParser::T__23);
    setState(905);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SolidityParser::T__13: {
        setState(903);
        assemblyBlock();
        break;
      }

      case SolidityParser::T__12:
      case SolidityParser::T__33:
      case SolidityParser::T__39:
      case SolidityParser::T__45:
      case SolidityParser::T__51:
      case SolidityParser::DecimalNumber:
      case SolidityParser::HexNumber:
      case SolidityParser::HexLiteral:
      case SolidityParser::Identifier:
      case SolidityParser::StringLiteral: {
        setState(904);
        assemblyExpression();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(907);
    assemblyExpression();
    setState(910);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SolidityParser::T__13: {
        setState(908);
        assemblyBlock();
        break;
      }

      case SolidityParser::T__12:
      case SolidityParser::T__33:
      case SolidityParser::T__39:
      case SolidityParser::T__45:
      case SolidityParser::T__51:
      case SolidityParser::DecimalNumber:
      case SolidityParser::HexNumber:
      case SolidityParser::HexLiteral:
      case SolidityParser::Identifier:
      case SolidityParser::StringLiteral: {
        setState(909);
        assemblyExpression();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(912);
    assemblyBlock();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssemblyIfContext ------------------------------------------------------------------

SolidityParser::AssemblyIfContext::AssemblyIfContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SolidityParser::AssemblyExpressionContext* SolidityParser::AssemblyIfContext::assemblyExpression() {
  return getRuleContext<SolidityParser::AssemblyExpressionContext>(0);
}

SolidityParser::AssemblyBlockContext* SolidityParser::AssemblyIfContext::assemblyBlock() {
  return getRuleContext<SolidityParser::AssemblyBlockContext>(0);
}


size_t SolidityParser::AssemblyIfContext::getRuleIndex() const {
  return SolidityParser::RuleAssemblyIf;
}


antlrcpp::Any SolidityParser::AssemblyIfContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitAssemblyIf(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::AssemblyIfContext* SolidityParser::assemblyIf() {
  AssemblyIfContext *_localctx = _tracker.createInstance<AssemblyIfContext>(_ctx, getState());
  enterRule(_localctx, 154, SolidityParser::RuleAssemblyIf);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(914);
    match(SolidityParser::T__40);
    setState(915);
    assemblyExpression();
    setState(916);
    assemblyBlock();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssemblyLiteralContext ------------------------------------------------------------------

SolidityParser::AssemblyLiteralContext::AssemblyLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SolidityParser::AssemblyLiteralContext::StringLiteral() {
  return getToken(SolidityParser::StringLiteral, 0);
}

tree::TerminalNode* SolidityParser::AssemblyLiteralContext::DecimalNumber() {
  return getToken(SolidityParser::DecimalNumber, 0);
}

tree::TerminalNode* SolidityParser::AssemblyLiteralContext::HexNumber() {
  return getToken(SolidityParser::HexNumber, 0);
}

tree::TerminalNode* SolidityParser::AssemblyLiteralContext::HexLiteral() {
  return getToken(SolidityParser::HexLiteral, 0);
}


size_t SolidityParser::AssemblyLiteralContext::getRuleIndex() const {
  return SolidityParser::RuleAssemblyLiteral;
}


antlrcpp::Any SolidityParser::AssemblyLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitAssemblyLiteral(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::AssemblyLiteralContext* SolidityParser::assemblyLiteral() {
  AssemblyLiteralContext *_localctx = _tracker.createInstance<AssemblyLiteralContext>(_ctx, getState());
  enterRule(_localctx, 156, SolidityParser::RuleAssemblyLiteral);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(918);
    _la = _input->LA(1);
    if (!(((((_la - 98) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 98)) & ((1ULL << (SolidityParser::DecimalNumber - 98))
      | (1ULL << (SolidityParser::HexNumber - 98))
      | (1ULL << (SolidityParser::HexLiteral - 98))
      | (1ULL << (SolidityParser::StringLiteral - 98)))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SubAssemblyContext ------------------------------------------------------------------

SolidityParser::SubAssemblyContext::SubAssemblyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SolidityParser::IdentifierContext* SolidityParser::SubAssemblyContext::identifier() {
  return getRuleContext<SolidityParser::IdentifierContext>(0);
}

SolidityParser::AssemblyBlockContext* SolidityParser::SubAssemblyContext::assemblyBlock() {
  return getRuleContext<SolidityParser::AssemblyBlockContext>(0);
}


size_t SolidityParser::SubAssemblyContext::getRuleIndex() const {
  return SolidityParser::RuleSubAssembly;
}


antlrcpp::Any SolidityParser::SubAssemblyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitSubAssembly(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::SubAssemblyContext* SolidityParser::subAssembly() {
  SubAssemblyContext *_localctx = _tracker.createInstance<SubAssemblyContext>(_ctx, getState());
  enterRule(_localctx, 158, SolidityParser::RuleSubAssembly);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(920);
    match(SolidityParser::T__43);
    setState(921);
    identifier();
    setState(922);
    assemblyBlock();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TupleExpressionContext ------------------------------------------------------------------

SolidityParser::TupleExpressionContext::TupleExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SolidityParser::ExpressionContext *> SolidityParser::TupleExpressionContext::expression() {
  return getRuleContexts<SolidityParser::ExpressionContext>();
}

SolidityParser::ExpressionContext* SolidityParser::TupleExpressionContext::expression(size_t i) {
  return getRuleContext<SolidityParser::ExpressionContext>(i);
}


size_t SolidityParser::TupleExpressionContext::getRuleIndex() const {
  return SolidityParser::RuleTupleExpression;
}


antlrcpp::Any SolidityParser::TupleExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitTupleExpression(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::TupleExpressionContext* SolidityParser::tupleExpression() {
  TupleExpressionContext *_localctx = _tracker.createInstance<TupleExpressionContext>(_ctx, getState());
  enterRule(_localctx, 160, SolidityParser::RuleTupleExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(950);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SolidityParser::T__20: {
        enterOuterAlt(_localctx, 1);
        setState(924);
        match(SolidityParser::T__20);

        setState(926);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << SolidityParser::T__3)
          | (1ULL << SolidityParser::T__12)
          | (1ULL << SolidityParser::T__20)
          | (1ULL << SolidityParser::T__31)
          | (1ULL << SolidityParser::T__33)
          | (1ULL << SolidityParser::T__39)
          | (1ULL << SolidityParser::T__48)
          | (1ULL << SolidityParser::T__49)
          | (1ULL << SolidityParser::T__50)
          | (1ULL << SolidityParser::T__51)
          | (1ULL << SolidityParser::T__52)
          | (1ULL << SolidityParser::T__53)
          | (1ULL << SolidityParser::T__54)
          | (1ULL << SolidityParser::T__55)
          | (1ULL << SolidityParser::T__56)
          | (1ULL << SolidityParser::T__57)
          | (1ULL << SolidityParser::T__58)
          | (1ULL << SolidityParser::T__59))) != 0) || ((((_la - 91) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 91)) & ((1ULL << (SolidityParser::Int - 91))
          | (1ULL << (SolidityParser::Uint - 91))
          | (1ULL << (SolidityParser::Byte - 91))
          | (1ULL << (SolidityParser::Fixed - 91))
          | (1ULL << (SolidityParser::Ufixed - 91))
          | (1ULL << (SolidityParser::BooleanLiteral - 91))
          | (1ULL << (SolidityParser::DecimalNumber - 91))
          | (1ULL << (SolidityParser::HexNumber - 91))
          | (1ULL << (SolidityParser::HexLiteral - 91))
          | (1ULL << (SolidityParser::Identifier - 91))
          | (1ULL << (SolidityParser::StringLiteral - 91)))) != 0)) {
          setState(925);
          expression(0);
        }
        setState(934);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == SolidityParser::T__14) {
          setState(928);
          match(SolidityParser::T__14);
          setState(930);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if ((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & ((1ULL << SolidityParser::T__3)
            | (1ULL << SolidityParser::T__12)
            | (1ULL << SolidityParser::T__20)
            | (1ULL << SolidityParser::T__31)
            | (1ULL << SolidityParser::T__33)
            | (1ULL << SolidityParser::T__39)
            | (1ULL << SolidityParser::T__48)
            | (1ULL << SolidityParser::T__49)
            | (1ULL << SolidityParser::T__50)
            | (1ULL << SolidityParser::T__51)
            | (1ULL << SolidityParser::T__52)
            | (1ULL << SolidityParser::T__53)
            | (1ULL << SolidityParser::T__54)
            | (1ULL << SolidityParser::T__55)
            | (1ULL << SolidityParser::T__56)
            | (1ULL << SolidityParser::T__57)
            | (1ULL << SolidityParser::T__58)
            | (1ULL << SolidityParser::T__59))) != 0) || ((((_la - 91) & ~ 0x3fULL) == 0) &&
            ((1ULL << (_la - 91)) & ((1ULL << (SolidityParser::Int - 91))
            | (1ULL << (SolidityParser::Uint - 91))
            | (1ULL << (SolidityParser::Byte - 91))
            | (1ULL << (SolidityParser::Fixed - 91))
            | (1ULL << (SolidityParser::Ufixed - 91))
            | (1ULL << (SolidityParser::BooleanLiteral - 91))
            | (1ULL << (SolidityParser::DecimalNumber - 91))
            | (1ULL << (SolidityParser::HexNumber - 91))
            | (1ULL << (SolidityParser::HexLiteral - 91))
            | (1ULL << (SolidityParser::Identifier - 91))
            | (1ULL << (SolidityParser::StringLiteral - 91)))) != 0)) {
            setState(929);
            expression(0);
          }
          setState(936);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(937);
        match(SolidityParser::T__21);
        break;
      }

      case SolidityParser::T__31: {
        enterOuterAlt(_localctx, 2);
        setState(938);
        match(SolidityParser::T__31);
        setState(947);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << SolidityParser::T__3)
          | (1ULL << SolidityParser::T__12)
          | (1ULL << SolidityParser::T__20)
          | (1ULL << SolidityParser::T__31)
          | (1ULL << SolidityParser::T__33)
          | (1ULL << SolidityParser::T__39)
          | (1ULL << SolidityParser::T__48)
          | (1ULL << SolidityParser::T__49)
          | (1ULL << SolidityParser::T__50)
          | (1ULL << SolidityParser::T__51)
          | (1ULL << SolidityParser::T__52)
          | (1ULL << SolidityParser::T__53)
          | (1ULL << SolidityParser::T__54)
          | (1ULL << SolidityParser::T__55)
          | (1ULL << SolidityParser::T__56)
          | (1ULL << SolidityParser::T__57)
          | (1ULL << SolidityParser::T__58)
          | (1ULL << SolidityParser::T__59))) != 0) || ((((_la - 91) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 91)) & ((1ULL << (SolidityParser::Int - 91))
          | (1ULL << (SolidityParser::Uint - 91))
          | (1ULL << (SolidityParser::Byte - 91))
          | (1ULL << (SolidityParser::Fixed - 91))
          | (1ULL << (SolidityParser::Ufixed - 91))
          | (1ULL << (SolidityParser::BooleanLiteral - 91))
          | (1ULL << (SolidityParser::DecimalNumber - 91))
          | (1ULL << (SolidityParser::HexNumber - 91))
          | (1ULL << (SolidityParser::HexLiteral - 91))
          | (1ULL << (SolidityParser::Identifier - 91))
          | (1ULL << (SolidityParser::StringLiteral - 91)))) != 0)) {
          setState(939);
          expression(0);
          setState(944);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == SolidityParser::T__14) {
            setState(940);
            match(SolidityParser::T__14);
            setState(941);
            expression(0);
            setState(946);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(949);
        match(SolidityParser::T__32);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ElementaryTypeNameExpressionContext ------------------------------------------------------------------

SolidityParser::ElementaryTypeNameExpressionContext::ElementaryTypeNameExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SolidityParser::ElementaryTypeNameContext* SolidityParser::ElementaryTypeNameExpressionContext::elementaryTypeName() {
  return getRuleContext<SolidityParser::ElementaryTypeNameContext>(0);
}


size_t SolidityParser::ElementaryTypeNameExpressionContext::getRuleIndex() const {
  return SolidityParser::RuleElementaryTypeNameExpression;
}


antlrcpp::Any SolidityParser::ElementaryTypeNameExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitElementaryTypeNameExpression(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::ElementaryTypeNameExpressionContext* SolidityParser::elementaryTypeNameExpression() {
  ElementaryTypeNameExpressionContext *_localctx = _tracker.createInstance<ElementaryTypeNameExpressionContext>(_ctx, getState());
  enterRule(_localctx, 162, SolidityParser::RuleElementaryTypeNameExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(952);
    elementaryTypeName();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NumberLiteralContext ------------------------------------------------------------------

SolidityParser::NumberLiteralContext::NumberLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SolidityParser::NumberLiteralContext::DecimalNumber() {
  return getToken(SolidityParser::DecimalNumber, 0);
}

tree::TerminalNode* SolidityParser::NumberLiteralContext::HexNumber() {
  return getToken(SolidityParser::HexNumber, 0);
}

tree::TerminalNode* SolidityParser::NumberLiteralContext::NumberUnit() {
  return getToken(SolidityParser::NumberUnit, 0);
}


size_t SolidityParser::NumberLiteralContext::getRuleIndex() const {
  return SolidityParser::RuleNumberLiteral;
}


antlrcpp::Any SolidityParser::NumberLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitNumberLiteral(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::NumberLiteralContext* SolidityParser::numberLiteral() {
  NumberLiteralContext *_localctx = _tracker.createInstance<NumberLiteralContext>(_ctx, getState());
  enterRule(_localctx, 164, SolidityParser::RuleNumberLiteral);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(954);
    _la = _input->LA(1);
    if (!(_la == SolidityParser::DecimalNumber

    || _la == SolidityParser::HexNumber)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(956);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 103, _ctx)) {
    case 1: {
      setState(955);
      match(SolidityParser::NumberUnit);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IdentifierContext ------------------------------------------------------------------

SolidityParser::IdentifierContext::IdentifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SolidityParser::IdentifierContext::Identifier() {
  return getToken(SolidityParser::Identifier, 0);
}


size_t SolidityParser::IdentifierContext::getRuleIndex() const {
  return SolidityParser::RuleIdentifier;
}


antlrcpp::Any SolidityParser::IdentifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SolidityVisitor*>(visitor))
    return parserVisitor->visitIdentifier(this);
  else
    return visitor->visitChildren(this);
}

SolidityParser::IdentifierContext* SolidityParser::identifier() {
  IdentifierContext *_localctx = _tracker.createInstance<IdentifierContext>(_ctx, getState());
  enterRule(_localctx, 166, SolidityParser::RuleIdentifier);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(958);
    _la = _input->LA(1);
    if (!(_la == SolidityParser::T__12

    || _la == SolidityParser::T__39 || _la == SolidityParser::Identifier)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool SolidityParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 31: return typeNameSempred(dynamic_cast<TypeNameContext *>(context), predicateIndex);
    case 55: return expressionSempred(dynamic_cast<ExpressionContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool SolidityParser::typeNameSempred(TypeNameContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 3);

  default:
    break;
  }
  return true;
}

bool SolidityParser::expressionSempred(ExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 1: return precpred(_ctx, 14);
    case 2: return precpred(_ctx, 13);
    case 3: return precpred(_ctx, 12);
    case 4: return precpred(_ctx, 11);
    case 5: return precpred(_ctx, 10);
    case 6: return precpred(_ctx, 9);
    case 7: return precpred(_ctx, 8);
    case 8: return precpred(_ctx, 7);
    case 9: return precpred(_ctx, 6);
    case 10: return precpred(_ctx, 5);
    case 11: return precpred(_ctx, 4);
    case 12: return precpred(_ctx, 3);
    case 13: return precpred(_ctx, 2);
    case 14: return precpred(_ctx, 25);
    case 15: return precpred(_ctx, 23);
    case 16: return precpred(_ctx, 22);
    case 17: return precpred(_ctx, 21);

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> SolidityParser::_decisionToDFA;
atn::PredictionContextCache SolidityParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN SolidityParser::_atn;
std::vector<uint16_t> SolidityParser::_serializedATN;

std::vector<std::string> SolidityParser::_ruleNames = {
  "sourceUnit", "pragmaDirective", "pragmaName", "pragmaValue", "version", 
  "versionOperator", "versionConstraint", "importDeclaration", "importDirective", 
  "contractDefinition", "inheritanceSpecifier", "contractPart", "stateVariableDeclaration", 
  "usingForDeclaration", "structDefinition", "constructorDefinition", "modifierDefinition", 
  "modifierInvocation", "functionDefinition", "returnParameters", "modifierList", 
  "eventDefinition", "enumValue", "enumDefinition", "parameterList", "parameter", 
  "eventParameterList", "eventParameter", "functionTypeParameterList", "functionTypeParameter", 
  "variableDeclaration", "typeName", "userDefinedTypeName", "mapping", "functionTypeName", 
  "storageLocation", "stateMutability", "block", "statement", "expressionStatement", 
  "ifStatement", "whileStatement", "simpleStatement", "forStatement", "inlineAssemblyStatement", 
  "doWhileStatement", "continueStatement", "breakStatement", "returnStatement", 
  "throwStatement", "emitStatement", "variableDeclarationStatement", "variableDeclarationList", 
  "identifierList", "elementaryTypeName", "expression", "primaryExpression", 
  "expressionList", "nameValueList", "nameValue", "functionCallArguments", 
  "functionCall", "assemblyBlock", "assemblyItem", "assemblyExpression", 
  "assemblyCall", "assemblyLocalDefinition", "assemblyAssignment", "assemblyIdentifierOrList", 
  "assemblyIdentifierList", "assemblyStackAssignment", "labelDefinition", 
  "assemblySwitch", "assemblyCase", "assemblyFunctionDefinition", "assemblyFunctionReturns", 
  "assemblyFor", "assemblyIf", "assemblyLiteral", "subAssembly", "tupleExpression", 
  "elementaryTypeNameExpression", "numberLiteral", "identifier"
};

std::vector<std::string> SolidityParser::_literalNames = {
  "", "'pragma'", "';'", "'^'", "'~'", "'>='", "'>'", "'<'", "'<='", "'='", 
  "'as'", "'import'", "'*'", "'from'", "'{'", "','", "'}'", "'contract'", 
  "'interface'", "'library'", "'is'", "'('", "')'", "'using'", "'for'", 
  "'struct'", "'constructor'", "'modifier'", "'function'", "'returns'", 
  "'event'", "'enum'", "'['", "']'", "'address'", "'.'", "'mapping'", "'=>'", 
  "'memory'", "'storage'", "'calldata'", "'if'", "'else'", "'while'", "'assembly'", 
  "'do'", "'return'", "'throw'", "'emit'", "'var'", "'bool'", "'string'", 
  "'byte'", "'++'", "'--'", "'new'", "'+'", "'-'", "'after'", "'delete'", 
  "'!'", "'**'", "'/'", "'%'", "'<<'", "'>>'", "'&'", "'|'", "'=='", "'!='", 
  "'&&'", "'||'", "'?'", "':'", "'|='", "'^='", "'&='", "'<<='", "'>>='", 
  "'+='", "'-='", "'*='", "'/='", "'%='", "'let'", "':='", "'=:'", "'switch'", 
  "'case'", "'default'", "'->'", "", "", "", "", "", "", "", "", "", "", 
  "", "", "'anonymous'", "'break'", "'constant'", "'continue'", "'external'", 
  "'indexed'", "'internal'", "'payable'", "'private'", "'public'", "'pure'", 
  "'view'"
};

std::vector<std::string> SolidityParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "Int", "Uint", "Byte", "Fixed", "Ufixed", "VersionLiteral", "BooleanLiteral", 
  "DecimalNumber", "HexNumber", "NumberUnit", "HexLiteral", "ReservedKeyword", 
  "AnonymousKeyword", "BreakKeyword", "ConstantKeyword", "ContinueKeyword", 
  "ExternalKeyword", "IndexedKeyword", "InternalKeyword", "PayableKeyword", 
  "PrivateKeyword", "PublicKeyword", "PureKeyword", "ViewKeyword", "Identifier", 
  "StringLiteral", "WS", "COMMENT", "LINE_COMMENT"
};

dfa::Vocabulary SolidityParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> SolidityParser::_tokenNames;

SolidityParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0x79, 0x3c3, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
    0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 
    0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 
    0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 
    0x4, 0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x4, 
    0x12, 0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 0x9, 0x14, 0x4, 0x15, 
    0x9, 0x15, 0x4, 0x16, 0x9, 0x16, 0x4, 0x17, 0x9, 0x17, 0x4, 0x18, 0x9, 
    0x18, 0x4, 0x19, 0x9, 0x19, 0x4, 0x1a, 0x9, 0x1a, 0x4, 0x1b, 0x9, 0x1b, 
    0x4, 0x1c, 0x9, 0x1c, 0x4, 0x1d, 0x9, 0x1d, 0x4, 0x1e, 0x9, 0x1e, 0x4, 
    0x1f, 0x9, 0x1f, 0x4, 0x20, 0x9, 0x20, 0x4, 0x21, 0x9, 0x21, 0x4, 0x22, 
    0x9, 0x22, 0x4, 0x23, 0x9, 0x23, 0x4, 0x24, 0x9, 0x24, 0x4, 0x25, 0x9, 
    0x25, 0x4, 0x26, 0x9, 0x26, 0x4, 0x27, 0x9, 0x27, 0x4, 0x28, 0x9, 0x28, 
    0x4, 0x29, 0x9, 0x29, 0x4, 0x2a, 0x9, 0x2a, 0x4, 0x2b, 0x9, 0x2b, 0x4, 
    0x2c, 0x9, 0x2c, 0x4, 0x2d, 0x9, 0x2d, 0x4, 0x2e, 0x9, 0x2e, 0x4, 0x2f, 
    0x9, 0x2f, 0x4, 0x30, 0x9, 0x30, 0x4, 0x31, 0x9, 0x31, 0x4, 0x32, 0x9, 
    0x32, 0x4, 0x33, 0x9, 0x33, 0x4, 0x34, 0x9, 0x34, 0x4, 0x35, 0x9, 0x35, 
    0x4, 0x36, 0x9, 0x36, 0x4, 0x37, 0x9, 0x37, 0x4, 0x38, 0x9, 0x38, 0x4, 
    0x39, 0x9, 0x39, 0x4, 0x3a, 0x9, 0x3a, 0x4, 0x3b, 0x9, 0x3b, 0x4, 0x3c, 
    0x9, 0x3c, 0x4, 0x3d, 0x9, 0x3d, 0x4, 0x3e, 0x9, 0x3e, 0x4, 0x3f, 0x9, 
    0x3f, 0x4, 0x40, 0x9, 0x40, 0x4, 0x41, 0x9, 0x41, 0x4, 0x42, 0x9, 0x42, 
    0x4, 0x43, 0x9, 0x43, 0x4, 0x44, 0x9, 0x44, 0x4, 0x45, 0x9, 0x45, 0x4, 
    0x46, 0x9, 0x46, 0x4, 0x47, 0x9, 0x47, 0x4, 0x48, 0x9, 0x48, 0x4, 0x49, 
    0x9, 0x49, 0x4, 0x4a, 0x9, 0x4a, 0x4, 0x4b, 0x9, 0x4b, 0x4, 0x4c, 0x9, 
    0x4c, 0x4, 0x4d, 0x9, 0x4d, 0x4, 0x4e, 0x9, 0x4e, 0x4, 0x4f, 0x9, 0x4f, 
    0x4, 0x50, 0x9, 0x50, 0x4, 0x51, 0x9, 0x51, 0x4, 0x52, 0x9, 0x52, 0x4, 
    0x53, 0x9, 0x53, 0x4, 0x54, 0x9, 0x54, 0x4, 0x55, 0x9, 0x55, 0x3, 0x2, 
    0x3, 0x2, 0x3, 0x2, 0x7, 0x2, 0xae, 0xa, 0x2, 0xc, 0x2, 0xe, 0x2, 0xb1, 
    0xb, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x4, 
    0x3, 0x4, 0x3, 0x5, 0x3, 0x5, 0x5, 0x5, 0xbc, 0xa, 0x5, 0x3, 0x6, 0x3, 
    0x6, 0x5, 0x6, 0xc0, 0xa, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x8, 0x5, 0x8, 
    0xc5, 0xa, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x5, 
    0x9, 0xcc, 0xa, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x5, 0xa, 
    0xd2, 0xa, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x5, 0xa, 0xd8, 
    0xa, 0xa, 0x3, 0xa, 0x3, 0xa, 0x5, 0xa, 0xdc, 0xa, 0xa, 0x3, 0xa, 0x3, 
    0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x7, 
    0xa, 0xe6, 0xa, 0xa, 0xc, 0xa, 0xe, 0xa, 0xe9, 0xb, 0xa, 0x3, 0xa, 0x3, 
    0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x5, 0xa, 0xf0, 0xa, 0xa, 0x3, 0xb, 
    0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x7, 0xb, 0xf8, 0xa, 
    0xb, 0xc, 0xb, 0xe, 0xb, 0xfb, 0xb, 0xb, 0x5, 0xb, 0xfd, 0xa, 0xb, 0x3, 
    0xb, 0x3, 0xb, 0x7, 0xb, 0x101, 0xa, 0xb, 0xc, 0xb, 0xe, 0xb, 0x104, 
    0xb, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 
    0x3, 0xc, 0x7, 0xc, 0x10d, 0xa, 0xc, 0xc, 0xc, 0xe, 0xc, 0x110, 0xb, 
    0xc, 0x3, 0xc, 0x3, 0xc, 0x5, 0xc, 0x114, 0xa, 0xc, 0x3, 0xd, 0x3, 0xd, 
    0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x5, 0xd, 
    0x11e, 0xa, 0xd, 0x3, 0xe, 0x3, 0xe, 0x7, 0xe, 0x122, 0xa, 0xe, 0xc, 
    0xe, 0xe, 0xe, 0x125, 0xb, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x5, 0xe, 
    0x12a, 0xa, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 
    0xf, 0x3, 0xf, 0x5, 0xf, 0x133, 0xa, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0x10, 
    0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 
    0x10, 0x7, 0x10, 0x13f, 0xa, 0x10, 0xc, 0x10, 0xe, 0x10, 0x142, 0xb, 
    0x10, 0x5, 0x10, 0x144, 0xa, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x11, 
    0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x12, 0x3, 0x12, 0x3, 
    0x12, 0x5, 0x12, 0x150, 0xa, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x13, 
    0x3, 0x13, 0x3, 0x13, 0x5, 0x13, 0x157, 0xa, 0x13, 0x3, 0x13, 0x5, 0x13, 
    0x15a, 0xa, 0x13, 0x3, 0x14, 0x3, 0x14, 0x5, 0x14, 0x15e, 0xa, 0x14, 
    0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x5, 0x14, 0x163, 0xa, 0x14, 0x3, 0x14, 
    0x3, 0x14, 0x5, 0x14, 0x167, 0xa, 0x14, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 
    0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x7, 
    0x16, 0x172, 0xa, 0x16, 0xc, 0x16, 0xe, 0x16, 0x175, 0xb, 0x16, 0x3, 
    0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x5, 0x17, 0x17b, 0xa, 0x17, 
    0x3, 0x17, 0x3, 0x17, 0x3, 0x18, 0x3, 0x18, 0x3, 0x19, 0x3, 0x19, 0x3, 
    0x19, 0x3, 0x19, 0x5, 0x19, 0x185, 0xa, 0x19, 0x3, 0x19, 0x3, 0x19, 
    0x7, 0x19, 0x189, 0xa, 0x19, 0xc, 0x19, 0xe, 0x19, 0x18c, 0xb, 0x19, 
    0x3, 0x19, 0x3, 0x19, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x7, 
    0x1a, 0x194, 0xa, 0x1a, 0xc, 0x1a, 0xe, 0x1a, 0x197, 0xb, 0x1a, 0x5, 
    0x1a, 0x199, 0xa, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1b, 0x3, 0x1b, 
    0x5, 0x1b, 0x19f, 0xa, 0x1b, 0x3, 0x1b, 0x5, 0x1b, 0x1a2, 0xa, 0x1b, 
    0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x7, 0x1c, 0x1a8, 0xa, 0x1c, 
    0xc, 0x1c, 0xe, 0x1c, 0x1ab, 0xb, 0x1c, 0x5, 0x1c, 0x1ad, 0xa, 0x1c, 
    0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1d, 0x3, 0x1d, 0x5, 0x1d, 0x1b3, 0xa, 0x1d, 
    0x3, 0x1d, 0x5, 0x1d, 0x1b6, 0xa, 0x1d, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 
    0x3, 0x1e, 0x7, 0x1e, 0x1bc, 0xa, 0x1e, 0xc, 0x1e, 0xe, 0x1e, 0x1bf, 
    0xb, 0x1e, 0x5, 0x1e, 0x1c1, 0xa, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1f, 
    0x3, 0x1f, 0x5, 0x1f, 0x1c7, 0xa, 0x1f, 0x3, 0x20, 0x3, 0x20, 0x5, 0x20, 
    0x1cb, 0xa, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 
    0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 0x5, 0x21, 0x1d6, 0xa, 0x21, 
    0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 0x5, 0x21, 0x1db, 0xa, 0x21, 0x3, 0x21, 
    0x7, 0x21, 0x1de, 0xa, 0x21, 0xc, 0x21, 0xe, 0x21, 0x1e1, 0xb, 0x21, 
    0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x7, 0x22, 0x1e6, 0xa, 0x22, 0xc, 0x22, 
    0xe, 0x22, 0x1e9, 0xb, 0x22, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 
    0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x24, 0x3, 0x24, 0x3, 0x24, 0x3, 
    0x24, 0x3, 0x24, 0x7, 0x24, 0x1f7, 0xa, 0x24, 0xc, 0x24, 0xe, 0x24, 
    0x1fa, 0xb, 0x24, 0x3, 0x24, 0x3, 0x24, 0x5, 0x24, 0x1fe, 0xa, 0x24, 
    0x3, 0x25, 0x3, 0x25, 0x3, 0x26, 0x3, 0x26, 0x3, 0x27, 0x3, 0x27, 0x7, 
    0x27, 0x206, 0xa, 0x27, 0xc, 0x27, 0xe, 0x27, 0x209, 0xb, 0x27, 0x3, 
    0x27, 0x3, 0x27, 0x3, 0x28, 0x3, 0x28, 0x3, 0x28, 0x3, 0x28, 0x3, 0x28, 
    0x3, 0x28, 0x3, 0x28, 0x3, 0x28, 0x3, 0x28, 0x3, 0x28, 0x3, 0x28, 0x3, 
    0x28, 0x5, 0x28, 0x219, 0xa, 0x28, 0x3, 0x29, 0x3, 0x29, 0x3, 0x29, 
    0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 
    0x2a, 0x5, 0x2a, 0x225, 0xa, 0x2a, 0x3, 0x2b, 0x3, 0x2b, 0x3, 0x2b, 
    0x3, 0x2b, 0x3, 0x2b, 0x3, 0x2b, 0x3, 0x2c, 0x3, 0x2c, 0x5, 0x2c, 0x22f, 
    0xa, 0x2c, 0x3, 0x2d, 0x3, 0x2d, 0x3, 0x2d, 0x3, 0x2d, 0x5, 0x2d, 0x235, 
    0xa, 0x2d, 0x3, 0x2d, 0x3, 0x2d, 0x5, 0x2d, 0x239, 0xa, 0x2d, 0x3, 0x2d, 
    0x5, 0x2d, 0x23c, 0xa, 0x2d, 0x3, 0x2d, 0x3, 0x2d, 0x3, 0x2d, 0x3, 0x2e, 
    0x3, 0x2e, 0x5, 0x2e, 0x243, 0xa, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2f, 
    0x3, 0x2f, 0x3, 0x2f, 0x3, 0x2f, 0x3, 0x2f, 0x3, 0x2f, 0x3, 0x2f, 0x3, 
    0x2f, 0x3, 0x30, 0x3, 0x30, 0x3, 0x30, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 
    0x3, 0x32, 0x3, 0x32, 0x5, 0x32, 0x257, 0xa, 0x32, 0x3, 0x32, 0x3, 0x32, 
    0x3, 0x33, 0x3, 0x33, 0x3, 0x33, 0x3, 0x34, 0x3, 0x34, 0x3, 0x34, 0x3, 
    0x34, 0x3, 0x35, 0x3, 0x35, 0x3, 0x35, 0x3, 0x35, 0x3, 0x35, 0x3, 0x35, 
    0x3, 0x35, 0x5, 0x35, 0x269, 0xa, 0x35, 0x3, 0x35, 0x3, 0x35, 0x5, 0x35, 
    0x26d, 0xa, 0x35, 0x3, 0x35, 0x3, 0x35, 0x3, 0x36, 0x5, 0x36, 0x272, 
    0xa, 0x36, 0x3, 0x36, 0x3, 0x36, 0x5, 0x36, 0x276, 0xa, 0x36, 0x7, 0x36, 
    0x278, 0xa, 0x36, 0xc, 0x36, 0xe, 0x36, 0x27b, 0xb, 0x36, 0x3, 0x37, 
    0x3, 0x37, 0x5, 0x37, 0x27f, 0xa, 0x37, 0x3, 0x37, 0x7, 0x37, 0x282, 
    0xa, 0x37, 0xc, 0x37, 0xe, 0x37, 0x285, 0xb, 0x37, 0x3, 0x37, 0x5, 0x37, 
    0x288, 0xa, 0x37, 0x3, 0x37, 0x3, 0x37, 0x3, 0x38, 0x3, 0x38, 0x3, 0x39, 
    0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 
    0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 
    0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x5, 0x39, 0x2a0, 0xa, 0x39, 
    0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 
    0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 
    0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 
    0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 
    0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 
    0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 
    0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 
    0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 
    0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x7, 0x39, 0x2db, 
    0xa, 0x39, 0xc, 0x39, 0xe, 0x39, 0x2de, 0xb, 0x39, 0x3, 0x3a, 0x3, 0x3a, 
    0x3, 0x3a, 0x3, 0x3a, 0x3, 0x3a, 0x3, 0x3a, 0x3, 0x3a, 0x5, 0x3a, 0x2e7, 
    0xa, 0x3a, 0x3, 0x3a, 0x3, 0x3a, 0x3, 0x3a, 0x3, 0x3a, 0x5, 0x3a, 0x2ed, 
    0xa, 0x3a, 0x5, 0x3a, 0x2ef, 0xa, 0x3a, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 
    0x7, 0x3b, 0x2f4, 0xa, 0x3b, 0xc, 0x3b, 0xe, 0x3b, 0x2f7, 0xb, 0x3b, 
    0x3, 0x3c, 0x3, 0x3c, 0x3, 0x3c, 0x7, 0x3c, 0x2fc, 0xa, 0x3c, 0xc, 0x3c, 
    0xe, 0x3c, 0x2ff, 0xb, 0x3c, 0x3, 0x3c, 0x5, 0x3c, 0x302, 0xa, 0x3c, 
    0x3, 0x3d, 0x3, 0x3d, 0x3, 0x3d, 0x3, 0x3d, 0x3, 0x3e, 0x3, 0x3e, 0x5, 
    0x3e, 0x30a, 0xa, 0x3e, 0x3, 0x3e, 0x3, 0x3e, 0x5, 0x3e, 0x30e, 0xa, 
    0x3e, 0x5, 0x3e, 0x310, 0xa, 0x3e, 0x3, 0x3f, 0x3, 0x3f, 0x3, 0x3f, 
    0x3, 0x3f, 0x3, 0x3f, 0x3, 0x40, 0x3, 0x40, 0x7, 0x40, 0x319, 0xa, 0x40, 
    0xc, 0x40, 0xe, 0x40, 0x31c, 0xb, 0x40, 0x3, 0x40, 0x3, 0x40, 0x3, 0x41, 
    0x3, 0x41, 0x3, 0x41, 0x3, 0x41, 0x3, 0x41, 0x3, 0x41, 0x3, 0x41, 0x3, 
    0x41, 0x3, 0x41, 0x3, 0x41, 0x3, 0x41, 0x3, 0x41, 0x3, 0x41, 0x3, 0x41, 
    0x3, 0x41, 0x3, 0x41, 0x3, 0x41, 0x5, 0x41, 0x331, 0xa, 0x41, 0x3, 0x42, 
    0x3, 0x42, 0x5, 0x42, 0x335, 0xa, 0x42, 0x3, 0x43, 0x3, 0x43, 0x3, 0x43, 
    0x3, 0x43, 0x5, 0x43, 0x33b, 0xa, 0x43, 0x3, 0x43, 0x3, 0x43, 0x5, 0x43, 
    0x33f, 0xa, 0x43, 0x3, 0x43, 0x3, 0x43, 0x7, 0x43, 0x343, 0xa, 0x43, 
    0xc, 0x43, 0xe, 0x43, 0x346, 0xb, 0x43, 0x3, 0x43, 0x5, 0x43, 0x349, 
    0xa, 0x43, 0x3, 0x44, 0x3, 0x44, 0x3, 0x44, 0x3, 0x44, 0x5, 0x44, 0x34f, 
    0xa, 0x44, 0x3, 0x45, 0x3, 0x45, 0x3, 0x45, 0x3, 0x45, 0x3, 0x46, 0x3, 
    0x46, 0x3, 0x46, 0x3, 0x46, 0x3, 0x46, 0x5, 0x46, 0x35a, 0xa, 0x46, 
    0x3, 0x47, 0x3, 0x47, 0x3, 0x47, 0x7, 0x47, 0x35f, 0xa, 0x47, 0xc, 0x47, 
    0xe, 0x47, 0x362, 0xb, 0x47, 0x3, 0x48, 0x3, 0x48, 0x3, 0x48, 0x3, 0x49, 
    0x3, 0x49, 0x3, 0x49, 0x3, 0x4a, 0x3, 0x4a, 0x3, 0x4a, 0x7, 0x4a, 0x36d, 
    0xa, 0x4a, 0xc, 0x4a, 0xe, 0x4a, 0x370, 0xb, 0x4a, 0x3, 0x4b, 0x3, 0x4b, 
    0x3, 0x4b, 0x3, 0x4b, 0x3, 0x4b, 0x3, 0x4b, 0x5, 0x4b, 0x378, 0xa, 0x4b, 
    0x3, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 0x5, 0x4c, 0x37e, 0xa, 0x4c, 
    0x3, 0x4c, 0x3, 0x4c, 0x5, 0x4c, 0x382, 0xa, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 
    0x3, 0x4d, 0x3, 0x4d, 0x3, 0x4d, 0x3, 0x4e, 0x3, 0x4e, 0x3, 0x4e, 0x5, 
    0x4e, 0x38c, 0xa, 0x4e, 0x3, 0x4e, 0x3, 0x4e, 0x3, 0x4e, 0x5, 0x4e, 
    0x391, 0xa, 0x4e, 0x3, 0x4e, 0x3, 0x4e, 0x3, 0x4f, 0x3, 0x4f, 0x3, 0x4f, 
    0x3, 0x4f, 0x3, 0x50, 0x3, 0x50, 0x3, 0x51, 0x3, 0x51, 0x3, 0x51, 0x3, 
    0x51, 0x3, 0x52, 0x3, 0x52, 0x5, 0x52, 0x3a1, 0xa, 0x52, 0x3, 0x52, 
    0x3, 0x52, 0x5, 0x52, 0x3a5, 0xa, 0x52, 0x7, 0x52, 0x3a7, 0xa, 0x52, 
    0xc, 0x52, 0xe, 0x52, 0x3aa, 0xb, 0x52, 0x3, 0x52, 0x3, 0x52, 0x3, 0x52, 
    0x3, 0x52, 0x3, 0x52, 0x7, 0x52, 0x3b1, 0xa, 0x52, 0xc, 0x52, 0xe, 0x52, 
    0x3b4, 0xb, 0x52, 0x5, 0x52, 0x3b6, 0xa, 0x52, 0x3, 0x52, 0x5, 0x52, 
    0x3b9, 0xa, 0x52, 0x3, 0x53, 0x3, 0x53, 0x3, 0x54, 0x3, 0x54, 0x5, 0x54, 
    0x3bf, 0xa, 0x54, 0x3, 0x55, 0x3, 0x55, 0x3, 0x55, 0x2, 0x4, 0x40, 0x70, 
    0x56, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 
    0x1a, 0x1c, 0x1e, 0x20, 0x22, 0x24, 0x26, 0x28, 0x2a, 0x2c, 0x2e, 0x30, 
    0x32, 0x34, 0x36, 0x38, 0x3a, 0x3c, 0x3e, 0x40, 0x42, 0x44, 0x46, 0x48, 
    0x4a, 0x4c, 0x4e, 0x50, 0x52, 0x54, 0x56, 0x58, 0x5a, 0x5c, 0x5e, 0x60, 
    0x62, 0x64, 0x66, 0x68, 0x6a, 0x6c, 0x6e, 0x70, 0x72, 0x74, 0x76, 0x78, 
    0x7a, 0x7c, 0x7e, 0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c, 0x8e, 0x90, 
    0x92, 0x94, 0x96, 0x98, 0x9a, 0x9c, 0x9e, 0xa0, 0xa2, 0xa4, 0xa6, 0xa8, 
    0x2, 0x13, 0x3, 0x2, 0x5, 0xb, 0x3, 0x2, 0x13, 0x15, 0x5, 0x2, 0x6b, 
    0x6b, 0x6f, 0x6f, 0x71, 0x72, 0x3, 0x2, 0x28, 0x2a, 0x5, 0x2, 0x6b, 
    0x6b, 0x70, 0x70, 0x73, 0x74, 0x5, 0x2, 0x24, 0x24, 0x33, 0x36, 0x5d, 
    0x61, 0x3, 0x2, 0x37, 0x38, 0x3, 0x2, 0x3a, 0x3b, 0x3, 0x2, 0x3c, 0x3d, 
    0x4, 0x2, 0xe, 0xe, 0x40, 0x41, 0x3, 0x2, 0x42, 0x43, 0x3, 0x2, 0x7, 
    0xa, 0x3, 0x2, 0x46, 0x47, 0x4, 0x2, 0xb, 0xb, 0x4c, 0x55, 0x5, 0x2, 
    0x64, 0x65, 0x67, 0x67, 0x76, 0x76, 0x3, 0x2, 0x64, 0x65, 0x5, 0x2, 
    0xf, 0xf, 0x2a, 0x2a, 0x75, 0x75, 0x2, 0x41c, 0x2, 0xaf, 0x3, 0x2, 0x2, 
    0x2, 0x4, 0xb2, 0x3, 0x2, 0x2, 0x2, 0x6, 0xb7, 0x3, 0x2, 0x2, 0x2, 0x8, 
    0xbb, 0x3, 0x2, 0x2, 0x2, 0xa, 0xbd, 0x3, 0x2, 0x2, 0x2, 0xc, 0xc1, 
    0x3, 0x2, 0x2, 0x2, 0xe, 0xc4, 0x3, 0x2, 0x2, 0x2, 0x10, 0xc8, 0x3, 
    0x2, 0x2, 0x2, 0x12, 0xef, 0x3, 0x2, 0x2, 0x2, 0x14, 0xf1, 0x3, 0x2, 
    0x2, 0x2, 0x16, 0x107, 0x3, 0x2, 0x2, 0x2, 0x18, 0x11d, 0x3, 0x2, 0x2, 
    0x2, 0x1a, 0x11f, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x12d, 0x3, 0x2, 0x2, 0x2, 
    0x1e, 0x136, 0x3, 0x2, 0x2, 0x2, 0x20, 0x147, 0x3, 0x2, 0x2, 0x2, 0x22, 
    0x14c, 0x3, 0x2, 0x2, 0x2, 0x24, 0x153, 0x3, 0x2, 0x2, 0x2, 0x26, 0x15b, 
    0x3, 0x2, 0x2, 0x2, 0x28, 0x168, 0x3, 0x2, 0x2, 0x2, 0x2a, 0x173, 0x3, 
    0x2, 0x2, 0x2, 0x2c, 0x176, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x17e, 0x3, 0x2, 
    0x2, 0x2, 0x30, 0x180, 0x3, 0x2, 0x2, 0x2, 0x32, 0x18f, 0x3, 0x2, 0x2, 
    0x2, 0x34, 0x19c, 0x3, 0x2, 0x2, 0x2, 0x36, 0x1a3, 0x3, 0x2, 0x2, 0x2, 
    0x38, 0x1b0, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x1b7, 0x3, 0x2, 0x2, 0x2, 0x3c, 
    0x1c4, 0x3, 0x2, 0x2, 0x2, 0x3e, 0x1c8, 0x3, 0x2, 0x2, 0x2, 0x40, 0x1d5, 
    0x3, 0x2, 0x2, 0x2, 0x42, 0x1e2, 0x3, 0x2, 0x2, 0x2, 0x44, 0x1ea, 0x3, 
    0x2, 0x2, 0x2, 0x46, 0x1f1, 0x3, 0x2, 0x2, 0x2, 0x48, 0x1ff, 0x3, 0x2, 
    0x2, 0x2, 0x4a, 0x201, 0x3, 0x2, 0x2, 0x2, 0x4c, 0x203, 0x3, 0x2, 0x2, 
    0x2, 0x4e, 0x218, 0x3, 0x2, 0x2, 0x2, 0x50, 0x21a, 0x3, 0x2, 0x2, 0x2, 
    0x52, 0x21d, 0x3, 0x2, 0x2, 0x2, 0x54, 0x226, 0x3, 0x2, 0x2, 0x2, 0x56, 
    0x22e, 0x3, 0x2, 0x2, 0x2, 0x58, 0x230, 0x3, 0x2, 0x2, 0x2, 0x5a, 0x240, 
    0x3, 0x2, 0x2, 0x2, 0x5c, 0x246, 0x3, 0x2, 0x2, 0x2, 0x5e, 0x24e, 0x3, 
    0x2, 0x2, 0x2, 0x60, 0x251, 0x3, 0x2, 0x2, 0x2, 0x62, 0x254, 0x3, 0x2, 
    0x2, 0x2, 0x64, 0x25a, 0x3, 0x2, 0x2, 0x2, 0x66, 0x25d, 0x3, 0x2, 0x2, 
    0x2, 0x68, 0x268, 0x3, 0x2, 0x2, 0x2, 0x6a, 0x271, 0x3, 0x2, 0x2, 0x2, 
    0x6c, 0x27c, 0x3, 0x2, 0x2, 0x2, 0x6e, 0x28b, 0x3, 0x2, 0x2, 0x2, 0x70, 
    0x29f, 0x3, 0x2, 0x2, 0x2, 0x72, 0x2ee, 0x3, 0x2, 0x2, 0x2, 0x74, 0x2f0, 
    0x3, 0x2, 0x2, 0x2, 0x76, 0x2f8, 0x3, 0x2, 0x2, 0x2, 0x78, 0x303, 0x3, 
    0x2, 0x2, 0x2, 0x7a, 0x30f, 0x3, 0x2, 0x2, 0x2, 0x7c, 0x311, 0x3, 0x2, 
    0x2, 0x2, 0x7e, 0x316, 0x3, 0x2, 0x2, 0x2, 0x80, 0x330, 0x3, 0x2, 0x2, 
    0x2, 0x82, 0x334, 0x3, 0x2, 0x2, 0x2, 0x84, 0x33a, 0x3, 0x2, 0x2, 0x2, 
    0x86, 0x34a, 0x3, 0x2, 0x2, 0x2, 0x88, 0x350, 0x3, 0x2, 0x2, 0x2, 0x8a, 
    0x359, 0x3, 0x2, 0x2, 0x2, 0x8c, 0x35b, 0x3, 0x2, 0x2, 0x2, 0x8e, 0x363, 
    0x3, 0x2, 0x2, 0x2, 0x90, 0x366, 0x3, 0x2, 0x2, 0x2, 0x92, 0x369, 0x3, 
    0x2, 0x2, 0x2, 0x94, 0x377, 0x3, 0x2, 0x2, 0x2, 0x96, 0x379, 0x3, 0x2, 
    0x2, 0x2, 0x98, 0x385, 0x3, 0x2, 0x2, 0x2, 0x9a, 0x388, 0x3, 0x2, 0x2, 
    0x2, 0x9c, 0x394, 0x3, 0x2, 0x2, 0x2, 0x9e, 0x398, 0x3, 0x2, 0x2, 0x2, 
    0xa0, 0x39a, 0x3, 0x2, 0x2, 0x2, 0xa2, 0x3b8, 0x3, 0x2, 0x2, 0x2, 0xa4, 
    0x3ba, 0x3, 0x2, 0x2, 0x2, 0xa6, 0x3bc, 0x3, 0x2, 0x2, 0x2, 0xa8, 0x3c0, 
    0x3, 0x2, 0x2, 0x2, 0xaa, 0xae, 0x5, 0x4, 0x3, 0x2, 0xab, 0xae, 0x5, 
    0x12, 0xa, 0x2, 0xac, 0xae, 0x5, 0x14, 0xb, 0x2, 0xad, 0xaa, 0x3, 0x2, 
    0x2, 0x2, 0xad, 0xab, 0x3, 0x2, 0x2, 0x2, 0xad, 0xac, 0x3, 0x2, 0x2, 
    0x2, 0xae, 0xb1, 0x3, 0x2, 0x2, 0x2, 0xaf, 0xad, 0x3, 0x2, 0x2, 0x2, 
    0xaf, 0xb0, 0x3, 0x2, 0x2, 0x2, 0xb0, 0x3, 0x3, 0x2, 0x2, 0x2, 0xb1, 
    0xaf, 0x3, 0x2, 0x2, 0x2, 0xb2, 0xb3, 0x7, 0x3, 0x2, 0x2, 0xb3, 0xb4, 
    0x5, 0x6, 0x4, 0x2, 0xb4, 0xb5, 0x5, 0x8, 0x5, 0x2, 0xb5, 0xb6, 0x7, 
    0x4, 0x2, 0x2, 0xb6, 0x5, 0x3, 0x2, 0x2, 0x2, 0xb7, 0xb8, 0x5, 0xa8, 
    0x55, 0x2, 0xb8, 0x7, 0x3, 0x2, 0x2, 0x2, 0xb9, 0xbc, 0x5, 0xa, 0x6, 
    0x2, 0xba, 0xbc, 0x5, 0x70, 0x39, 0x2, 0xbb, 0xb9, 0x3, 0x2, 0x2, 0x2, 
    0xbb, 0xba, 0x3, 0x2, 0x2, 0x2, 0xbc, 0x9, 0x3, 0x2, 0x2, 0x2, 0xbd, 
    0xbf, 0x5, 0xe, 0x8, 0x2, 0xbe, 0xc0, 0x5, 0xe, 0x8, 0x2, 0xbf, 0xbe, 
    0x3, 0x2, 0x2, 0x2, 0xbf, 0xc0, 0x3, 0x2, 0x2, 0x2, 0xc0, 0xb, 0x3, 
    0x2, 0x2, 0x2, 0xc1, 0xc2, 0x9, 0x2, 0x2, 0x2, 0xc2, 0xd, 0x3, 0x2, 
    0x2, 0x2, 0xc3, 0xc5, 0x5, 0xc, 0x7, 0x2, 0xc4, 0xc3, 0x3, 0x2, 0x2, 
    0x2, 0xc4, 0xc5, 0x3, 0x2, 0x2, 0x2, 0xc5, 0xc6, 0x3, 0x2, 0x2, 0x2, 
    0xc6, 0xc7, 0x7, 0x62, 0x2, 0x2, 0xc7, 0xf, 0x3, 0x2, 0x2, 0x2, 0xc8, 
    0xcb, 0x5, 0xa8, 0x55, 0x2, 0xc9, 0xca, 0x7, 0xc, 0x2, 0x2, 0xca, 0xcc, 
    0x5, 0xa8, 0x55, 0x2, 0xcb, 0xc9, 0x3, 0x2, 0x2, 0x2, 0xcb, 0xcc, 0x3, 
    0x2, 0x2, 0x2, 0xcc, 0x11, 0x3, 0x2, 0x2, 0x2, 0xcd, 0xce, 0x7, 0xd, 
    0x2, 0x2, 0xce, 0xd1, 0x7, 0x76, 0x2, 0x2, 0xcf, 0xd0, 0x7, 0xc, 0x2, 
    0x2, 0xd0, 0xd2, 0x5, 0xa8, 0x55, 0x2, 0xd1, 0xcf, 0x3, 0x2, 0x2, 0x2, 
    0xd1, 0xd2, 0x3, 0x2, 0x2, 0x2, 0xd2, 0xd3, 0x3, 0x2, 0x2, 0x2, 0xd3, 
    0xf0, 0x7, 0x4, 0x2, 0x2, 0xd4, 0xd7, 0x7, 0xd, 0x2, 0x2, 0xd5, 0xd8, 
    0x7, 0xe, 0x2, 0x2, 0xd6, 0xd8, 0x5, 0xa8, 0x55, 0x2, 0xd7, 0xd5, 0x3, 
    0x2, 0x2, 0x2, 0xd7, 0xd6, 0x3, 0x2, 0x2, 0x2, 0xd8, 0xdb, 0x3, 0x2, 
    0x2, 0x2, 0xd9, 0xda, 0x7, 0xc, 0x2, 0x2, 0xda, 0xdc, 0x5, 0xa8, 0x55, 
    0x2, 0xdb, 0xd9, 0x3, 0x2, 0x2, 0x2, 0xdb, 0xdc, 0x3, 0x2, 0x2, 0x2, 
    0xdc, 0xdd, 0x3, 0x2, 0x2, 0x2, 0xdd, 0xde, 0x7, 0xf, 0x2, 0x2, 0xde, 
    0xdf, 0x7, 0x76, 0x2, 0x2, 0xdf, 0xf0, 0x7, 0x4, 0x2, 0x2, 0xe0, 0xe1, 
    0x7, 0xd, 0x2, 0x2, 0xe1, 0xe2, 0x7, 0x10, 0x2, 0x2, 0xe2, 0xe7, 0x5, 
    0x10, 0x9, 0x2, 0xe3, 0xe4, 0x7, 0x11, 0x2, 0x2, 0xe4, 0xe6, 0x5, 0x10, 
    0x9, 0x2, 0xe5, 0xe3, 0x3, 0x2, 0x2, 0x2, 0xe6, 0xe9, 0x3, 0x2, 0x2, 
    0x2, 0xe7, 0xe5, 0x3, 0x2, 0x2, 0x2, 0xe7, 0xe8, 0x3, 0x2, 0x2, 0x2, 
    0xe8, 0xea, 0x3, 0x2, 0x2, 0x2, 0xe9, 0xe7, 0x3, 0x2, 0x2, 0x2, 0xea, 
    0xeb, 0x7, 0x12, 0x2, 0x2, 0xeb, 0xec, 0x7, 0xf, 0x2, 0x2, 0xec, 0xed, 
    0x7, 0x76, 0x2, 0x2, 0xed, 0xee, 0x7, 0x4, 0x2, 0x2, 0xee, 0xf0, 0x3, 
    0x2, 0x2, 0x2, 0xef, 0xcd, 0x3, 0x2, 0x2, 0x2, 0xef, 0xd4, 0x3, 0x2, 
    0x2, 0x2, 0xef, 0xe0, 0x3, 0x2, 0x2, 0x2, 0xf0, 0x13, 0x3, 0x2, 0x2, 
    0x2, 0xf1, 0xf2, 0x9, 0x3, 0x2, 0x2, 0xf2, 0xfc, 0x5, 0xa8, 0x55, 0x2, 
    0xf3, 0xf4, 0x7, 0x16, 0x2, 0x2, 0xf4, 0xf9, 0x5, 0x16, 0xc, 0x2, 0xf5, 
    0xf6, 0x7, 0x11, 0x2, 0x2, 0xf6, 0xf8, 0x5, 0x16, 0xc, 0x2, 0xf7, 0xf5, 
    0x3, 0x2, 0x2, 0x2, 0xf8, 0xfb, 0x3, 0x2, 0x2, 0x2, 0xf9, 0xf7, 0x3, 
    0x2, 0x2, 0x2, 0xf9, 0xfa, 0x3, 0x2, 0x2, 0x2, 0xfa, 0xfd, 0x3, 0x2, 
    0x2, 0x2, 0xfb, 0xf9, 0x3, 0x2, 0x2, 0x2, 0xfc, 0xf3, 0x3, 0x2, 0x2, 
    0x2, 0xfc, 0xfd, 0x3, 0x2, 0x2, 0x2, 0xfd, 0xfe, 0x3, 0x2, 0x2, 0x2, 
    0xfe, 0x102, 0x7, 0x10, 0x2, 0x2, 0xff, 0x101, 0x5, 0x18, 0xd, 0x2, 
    0x100, 0xff, 0x3, 0x2, 0x2, 0x2, 0x101, 0x104, 0x3, 0x2, 0x2, 0x2, 0x102, 
    0x100, 0x3, 0x2, 0x2, 0x2, 0x102, 0x103, 0x3, 0x2, 0x2, 0x2, 0x103, 
    0x105, 0x3, 0x2, 0x2, 0x2, 0x104, 0x102, 0x3, 0x2, 0x2, 0x2, 0x105, 
    0x106, 0x7, 0x12, 0x2, 0x2, 0x106, 0x15, 0x3, 0x2, 0x2, 0x2, 0x107, 
    0x113, 0x5, 0x42, 0x22, 0x2, 0x108, 0x109, 0x7, 0x17, 0x2, 0x2, 0x109, 
    0x10e, 0x5, 0x70, 0x39, 0x2, 0x10a, 0x10b, 0x7, 0x11, 0x2, 0x2, 0x10b, 
    0x10d, 0x5, 0x70, 0x39, 0x2, 0x10c, 0x10a, 0x3, 0x2, 0x2, 0x2, 0x10d, 
    0x110, 0x3, 0x2, 0x2, 0x2, 0x10e, 0x10c, 0x3, 0x2, 0x2, 0x2, 0x10e, 
    0x10f, 0x3, 0x2, 0x2, 0x2, 0x10f, 0x111, 0x3, 0x2, 0x2, 0x2, 0x110, 
    0x10e, 0x3, 0x2, 0x2, 0x2, 0x111, 0x112, 0x7, 0x18, 0x2, 0x2, 0x112, 
    0x114, 0x3, 0x2, 0x2, 0x2, 0x113, 0x108, 0x3, 0x2, 0x2, 0x2, 0x113, 
    0x114, 0x3, 0x2, 0x2, 0x2, 0x114, 0x17, 0x3, 0x2, 0x2, 0x2, 0x115, 0x11e, 
    0x5, 0x1a, 0xe, 0x2, 0x116, 0x11e, 0x5, 0x1c, 0xf, 0x2, 0x117, 0x11e, 
    0x5, 0x1e, 0x10, 0x2, 0x118, 0x11e, 0x5, 0x20, 0x11, 0x2, 0x119, 0x11e, 
    0x5, 0x22, 0x12, 0x2, 0x11a, 0x11e, 0x5, 0x26, 0x14, 0x2, 0x11b, 0x11e, 
    0x5, 0x2c, 0x17, 0x2, 0x11c, 0x11e, 0x5, 0x30, 0x19, 0x2, 0x11d, 0x115, 
    0x3, 0x2, 0x2, 0x2, 0x11d, 0x116, 0x3, 0x2, 0x2, 0x2, 0x11d, 0x117, 
    0x3, 0x2, 0x2, 0x2, 0x11d, 0x118, 0x3, 0x2, 0x2, 0x2, 0x11d, 0x119, 
    0x3, 0x2, 0x2, 0x2, 0x11d, 0x11a, 0x3, 0x2, 0x2, 0x2, 0x11d, 0x11b, 
    0x3, 0x2, 0x2, 0x2, 0x11d, 0x11c, 0x3, 0x2, 0x2, 0x2, 0x11e, 0x19, 0x3, 
    0x2, 0x2, 0x2, 0x11f, 0x123, 0x5, 0x40, 0x21, 0x2, 0x120, 0x122, 0x9, 
    0x4, 0x2, 0x2, 0x121, 0x120, 0x3, 0x2, 0x2, 0x2, 0x122, 0x125, 0x3, 
    0x2, 0x2, 0x2, 0x123, 0x121, 0x3, 0x2, 0x2, 0x2, 0x123, 0x124, 0x3, 
    0x2, 0x2, 0x2, 0x124, 0x126, 0x3, 0x2, 0x2, 0x2, 0x125, 0x123, 0x3, 
    0x2, 0x2, 0x2, 0x126, 0x129, 0x5, 0xa8, 0x55, 0x2, 0x127, 0x128, 0x7, 
    0xb, 0x2, 0x2, 0x128, 0x12a, 0x5, 0x70, 0x39, 0x2, 0x129, 0x127, 0x3, 
    0x2, 0x2, 0x2, 0x129, 0x12a, 0x3, 0x2, 0x2, 0x2, 0x12a, 0x12b, 0x3, 
    0x2, 0x2, 0x2, 0x12b, 0x12c, 0x7, 0x4, 0x2, 0x2, 0x12c, 0x1b, 0x3, 0x2, 
    0x2, 0x2, 0x12d, 0x12e, 0x7, 0x19, 0x2, 0x2, 0x12e, 0x12f, 0x5, 0xa8, 
    0x55, 0x2, 0x12f, 0x132, 0x7, 0x1a, 0x2, 0x2, 0x130, 0x133, 0x7, 0xe, 
    0x2, 0x2, 0x131, 0x133, 0x5, 0x40, 0x21, 0x2, 0x132, 0x130, 0x3, 0x2, 
    0x2, 0x2, 0x132, 0x131, 0x3, 0x2, 0x2, 0x2, 0x133, 0x134, 0x3, 0x2, 
    0x2, 0x2, 0x134, 0x135, 0x7, 0x4, 0x2, 0x2, 0x135, 0x1d, 0x3, 0x2, 0x2, 
    0x2, 0x136, 0x137, 0x7, 0x1b, 0x2, 0x2, 0x137, 0x138, 0x5, 0xa8, 0x55, 
    0x2, 0x138, 0x143, 0x7, 0x10, 0x2, 0x2, 0x139, 0x13a, 0x5, 0x3e, 0x20, 
    0x2, 0x13a, 0x140, 0x7, 0x4, 0x2, 0x2, 0x13b, 0x13c, 0x5, 0x3e, 0x20, 
    0x2, 0x13c, 0x13d, 0x7, 0x4, 0x2, 0x2, 0x13d, 0x13f, 0x3, 0x2, 0x2, 
    0x2, 0x13e, 0x13b, 0x3, 0x2, 0x2, 0x2, 0x13f, 0x142, 0x3, 0x2, 0x2, 
    0x2, 0x140, 0x13e, 0x3, 0x2, 0x2, 0x2, 0x140, 0x141, 0x3, 0x2, 0x2, 
    0x2, 0x141, 0x144, 0x3, 0x2, 0x2, 0x2, 0x142, 0x140, 0x3, 0x2, 0x2, 
    0x2, 0x143, 0x139, 0x3, 0x2, 0x2, 0x2, 0x143, 0x144, 0x3, 0x2, 0x2, 
    0x2, 0x144, 0x145, 0x3, 0x2, 0x2, 0x2, 0x145, 0x146, 0x7, 0x12, 0x2, 
    0x2, 0x146, 0x1f, 0x3, 0x2, 0x2, 0x2, 0x147, 0x148, 0x7, 0x1c, 0x2, 
    0x2, 0x148, 0x149, 0x5, 0x32, 0x1a, 0x2, 0x149, 0x14a, 0x5, 0x2a, 0x16, 
    0x2, 0x14a, 0x14b, 0x5, 0x4c, 0x27, 0x2, 0x14b, 0x21, 0x3, 0x2, 0x2, 
    0x2, 0x14c, 0x14d, 0x7, 0x1d, 0x2, 0x2, 0x14d, 0x14f, 0x5, 0xa8, 0x55, 
    0x2, 0x14e, 0x150, 0x5, 0x32, 0x1a, 0x2, 0x14f, 0x14e, 0x3, 0x2, 0x2, 
    0x2, 0x14f, 0x150, 0x3, 0x2, 0x2, 0x2, 0x150, 0x151, 0x3, 0x2, 0x2, 
    0x2, 0x151, 0x152, 0x5, 0x4c, 0x27, 0x2, 0x152, 0x23, 0x3, 0x2, 0x2, 
    0x2, 0x153, 0x159, 0x5, 0xa8, 0x55, 0x2, 0x154, 0x156, 0x7, 0x17, 0x2, 
    0x2, 0x155, 0x157, 0x5, 0x74, 0x3b, 0x2, 0x156, 0x155, 0x3, 0x2, 0x2, 
    0x2, 0x156, 0x157, 0x3, 0x2, 0x2, 0x2, 0x157, 0x158, 0x3, 0x2, 0x2, 
    0x2, 0x158, 0x15a, 0x7, 0x18, 0x2, 0x2, 0x159, 0x154, 0x3, 0x2, 0x2, 
    0x2, 0x159, 0x15a, 0x3, 0x2, 0x2, 0x2, 0x15a, 0x25, 0x3, 0x2, 0x2, 0x2, 
    0x15b, 0x15d, 0x7, 0x1e, 0x2, 0x2, 0x15c, 0x15e, 0x5, 0xa8, 0x55, 0x2, 
    0x15d, 0x15c, 0x3, 0x2, 0x2, 0x2, 0x15d, 0x15e, 0x3, 0x2, 0x2, 0x2, 
    0x15e, 0x15f, 0x3, 0x2, 0x2, 0x2, 0x15f, 0x160, 0x5, 0x32, 0x1a, 0x2, 
    0x160, 0x162, 0x5, 0x2a, 0x16, 0x2, 0x161, 0x163, 0x5, 0x28, 0x15, 0x2, 
    0x162, 0x161, 0x3, 0x2, 0x2, 0x2, 0x162, 0x163, 0x3, 0x2, 0x2, 0x2, 
    0x163, 0x166, 0x3, 0x2, 0x2, 0x2, 0x164, 0x167, 0x7, 0x4, 0x2, 0x2, 
    0x165, 0x167, 0x5, 0x4c, 0x27, 0x2, 0x166, 0x164, 0x3, 0x2, 0x2, 0x2, 
    0x166, 0x165, 0x3, 0x2, 0x2, 0x2, 0x167, 0x27, 0x3, 0x2, 0x2, 0x2, 0x168, 
    0x169, 0x7, 0x1f, 0x2, 0x2, 0x169, 0x16a, 0x5, 0x32, 0x1a, 0x2, 0x16a, 
    0x29, 0x3, 0x2, 0x2, 0x2, 0x16b, 0x172, 0x5, 0x24, 0x13, 0x2, 0x16c, 
    0x172, 0x5, 0x4a, 0x26, 0x2, 0x16d, 0x172, 0x7, 0x6d, 0x2, 0x2, 0x16e, 
    0x172, 0x7, 0x72, 0x2, 0x2, 0x16f, 0x172, 0x7, 0x6f, 0x2, 0x2, 0x170, 
    0x172, 0x7, 0x71, 0x2, 0x2, 0x171, 0x16b, 0x3, 0x2, 0x2, 0x2, 0x171, 
    0x16c, 0x3, 0x2, 0x2, 0x2, 0x171, 0x16d, 0x3, 0x2, 0x2, 0x2, 0x171, 
    0x16e, 0x3, 0x2, 0x2, 0x2, 0x171, 0x16f, 0x3, 0x2, 0x2, 0x2, 0x171, 
    0x170, 0x3, 0x2, 0x2, 0x2, 0x172, 0x175, 0x3, 0x2, 0x2, 0x2, 0x173, 
    0x171, 0x3, 0x2, 0x2, 0x2, 0x173, 0x174, 0x3, 0x2, 0x2, 0x2, 0x174, 
    0x2b, 0x3, 0x2, 0x2, 0x2, 0x175, 0x173, 0x3, 0x2, 0x2, 0x2, 0x176, 0x177, 
    0x7, 0x20, 0x2, 0x2, 0x177, 0x178, 0x5, 0xa8, 0x55, 0x2, 0x178, 0x17a, 
    0x5, 0x36, 0x1c, 0x2, 0x179, 0x17b, 0x7, 0x69, 0x2, 0x2, 0x17a, 0x179, 
    0x3, 0x2, 0x2, 0x2, 0x17a, 0x17b, 0x3, 0x2, 0x2, 0x2, 0x17b, 0x17c, 
    0x3, 0x2, 0x2, 0x2, 0x17c, 0x17d, 0x7, 0x4, 0x2, 0x2, 0x17d, 0x2d, 0x3, 
    0x2, 0x2, 0x2, 0x17e, 0x17f, 0x5, 0xa8, 0x55, 0x2, 0x17f, 0x2f, 0x3, 
    0x2, 0x2, 0x2, 0x180, 0x181, 0x7, 0x21, 0x2, 0x2, 0x181, 0x182, 0x5, 
    0xa8, 0x55, 0x2, 0x182, 0x184, 0x7, 0x10, 0x2, 0x2, 0x183, 0x185, 0x5, 
    0x2e, 0x18, 0x2, 0x184, 0x183, 0x3, 0x2, 0x2, 0x2, 0x184, 0x185, 0x3, 
    0x2, 0x2, 0x2, 0x185, 0x18a, 0x3, 0x2, 0x2, 0x2, 0x186, 0x187, 0x7, 
    0x11, 0x2, 0x2, 0x187, 0x189, 0x5, 0x2e, 0x18, 0x2, 0x188, 0x186, 0x3, 
    0x2, 0x2, 0x2, 0x189, 0x18c, 0x3, 0x2, 0x2, 0x2, 0x18a, 0x188, 0x3, 
    0x2, 0x2, 0x2, 0x18a, 0x18b, 0x3, 0x2, 0x2, 0x2, 0x18b, 0x18d, 0x3, 
    0x2, 0x2, 0x2, 0x18c, 0x18a, 0x3, 0x2, 0x2, 0x2, 0x18d, 0x18e, 0x7, 
    0x12, 0x2, 0x2, 0x18e, 0x31, 0x3, 0x2, 0x2, 0x2, 0x18f, 0x198, 0x7, 
    0x17, 0x2, 0x2, 0x190, 0x195, 0x5, 0x34, 0x1b, 0x2, 0x191, 0x192, 0x7, 
    0x11, 0x2, 0x2, 0x192, 0x194, 0x5, 0x34, 0x1b, 0x2, 0x193, 0x191, 0x3, 
    0x2, 0x2, 0x2, 0x194, 0x197, 0x3, 0x2, 0x2, 0x2, 0x195, 0x193, 0x3, 
    0x2, 0x2, 0x2, 0x195, 0x196, 0x3, 0x2, 0x2, 0x2, 0x196, 0x199, 0x3, 
    0x2, 0x2, 0x2, 0x197, 0x195, 0x3, 0x2, 0x2, 0x2, 0x198, 0x190, 0x3, 
    0x2, 0x2, 0x2, 0x198, 0x199, 0x3, 0x2, 0x2, 0x2, 0x199, 0x19a, 0x3, 
    0x2, 0x2, 0x2, 0x19a, 0x19b, 0x7, 0x18, 0x2, 0x2, 0x19b, 0x33, 0x3, 
    0x2, 0x2, 0x2, 0x19c, 0x19e, 0x5, 0x40, 0x21, 0x2, 0x19d, 0x19f, 0x5, 
    0x48, 0x25, 0x2, 0x19e, 0x19d, 0x3, 0x2, 0x2, 0x2, 0x19e, 0x19f, 0x3, 
    0x2, 0x2, 0x2, 0x19f, 0x1a1, 0x3, 0x2, 0x2, 0x2, 0x1a0, 0x1a2, 0x5, 
    0xa8, 0x55, 0x2, 0x1a1, 0x1a0, 0x3, 0x2, 0x2, 0x2, 0x1a1, 0x1a2, 0x3, 
    0x2, 0x2, 0x2, 0x1a2, 0x35, 0x3, 0x2, 0x2, 0x2, 0x1a3, 0x1ac, 0x7, 0x17, 
    0x2, 0x2, 0x1a4, 0x1a9, 0x5, 0x38, 0x1d, 0x2, 0x1a5, 0x1a6, 0x7, 0x11, 
    0x2, 0x2, 0x1a6, 0x1a8, 0x5, 0x38, 0x1d, 0x2, 0x1a7, 0x1a5, 0x3, 0x2, 
    0x2, 0x2, 0x1a8, 0x1ab, 0x3, 0x2, 0x2, 0x2, 0x1a9, 0x1a7, 0x3, 0x2, 
    0x2, 0x2, 0x1a9, 0x1aa, 0x3, 0x2, 0x2, 0x2, 0x1aa, 0x1ad, 0x3, 0x2, 
    0x2, 0x2, 0x1ab, 0x1a9, 0x3, 0x2, 0x2, 0x2, 0x1ac, 0x1a4, 0x3, 0x2, 
    0x2, 0x2, 0x1ac, 0x1ad, 0x3, 0x2, 0x2, 0x2, 0x1ad, 0x1ae, 0x3, 0x2, 
    0x2, 0x2, 0x1ae, 0x1af, 0x7, 0x18, 0x2, 0x2, 0x1af, 0x37, 0x3, 0x2, 
    0x2, 0x2, 0x1b0, 0x1b2, 0x5, 0x40, 0x21, 0x2, 0x1b1, 0x1b3, 0x7, 0x6e, 
    0x2, 0x2, 0x1b2, 0x1b1, 0x3, 0x2, 0x2, 0x2, 0x1b2, 0x1b3, 0x3, 0x2, 
    0x2, 0x2, 0x1b3, 0x1b5, 0x3, 0x2, 0x2, 0x2, 0x1b4, 0x1b6, 0x5, 0xa8, 
    0x55, 0x2, 0x1b5, 0x1b4, 0x3, 0x2, 0x2, 0x2, 0x1b5, 0x1b6, 0x3, 0x2, 
    0x2, 0x2, 0x1b6, 0x39, 0x3, 0x2, 0x2, 0x2, 0x1b7, 0x1c0, 0x7, 0x17, 
    0x2, 0x2, 0x1b8, 0x1bd, 0x5, 0x3c, 0x1f, 0x2, 0x1b9, 0x1ba, 0x7, 0x11, 
    0x2, 0x2, 0x1ba, 0x1bc, 0x5, 0x3c, 0x1f, 0x2, 0x1bb, 0x1b9, 0x3, 0x2, 
    0x2, 0x2, 0x1bc, 0x1bf, 0x3, 0x2, 0x2, 0x2, 0x1bd, 0x1bb, 0x3, 0x2, 
    0x2, 0x2, 0x1bd, 0x1be, 0x3, 0x2, 0x2, 0x2, 0x1be, 0x1c1, 0x3, 0x2, 
    0x2, 0x2, 0x1bf, 0x1bd, 0x3, 0x2, 0x2, 0x2, 0x1c0, 0x1b8, 0x3, 0x2, 
    0x2, 0x2, 0x1c0, 0x1c1, 0x3, 0x2, 0x2, 0x2, 0x1c1, 0x1c2, 0x3, 0x2, 
    0x2, 0x2, 0x1c2, 0x1c3, 0x7, 0x18, 0x2, 0x2, 0x1c3, 0x3b, 0x3, 0x2, 
    0x2, 0x2, 0x1c4, 0x1c6, 0x5, 0x40, 0x21, 0x2, 0x1c5, 0x1c7, 0x5, 0x48, 
    0x25, 0x2, 0x1c6, 0x1c5, 0x3, 0x2, 0x2, 0x2, 0x1c6, 0x1c7, 0x3, 0x2, 
    0x2, 0x2, 0x1c7, 0x3d, 0x3, 0x2, 0x2, 0x2, 0x1c8, 0x1ca, 0x5, 0x40, 
    0x21, 0x2, 0x1c9, 0x1cb, 0x5, 0x48, 0x25, 0x2, 0x1ca, 0x1c9, 0x3, 0x2, 
    0x2, 0x2, 0x1ca, 0x1cb, 0x3, 0x2, 0x2, 0x2, 0x1cb, 0x1cc, 0x3, 0x2, 
    0x2, 0x2, 0x1cc, 0x1cd, 0x5, 0xa8, 0x55, 0x2, 0x1cd, 0x3f, 0x3, 0x2, 
    0x2, 0x2, 0x1ce, 0x1cf, 0x8, 0x21, 0x1, 0x2, 0x1cf, 0x1d6, 0x5, 0x6e, 
    0x38, 0x2, 0x1d0, 0x1d6, 0x5, 0x42, 0x22, 0x2, 0x1d1, 0x1d6, 0x5, 0x44, 
    0x23, 0x2, 0x1d2, 0x1d6, 0x5, 0x46, 0x24, 0x2, 0x1d3, 0x1d4, 0x7, 0x24, 
    0x2, 0x2, 0x1d4, 0x1d6, 0x7, 0x70, 0x2, 0x2, 0x1d5, 0x1ce, 0x3, 0x2, 
    0x2, 0x2, 0x1d5, 0x1d0, 0x3, 0x2, 0x2, 0x2, 0x1d5, 0x1d1, 0x3, 0x2, 
    0x2, 0x2, 0x1d5, 0x1d2, 0x3, 0x2, 0x2, 0x2, 0x1d5, 0x1d3, 0x3, 0x2, 
    0x2, 0x2, 0x1d6, 0x1df, 0x3, 0x2, 0x2, 0x2, 0x1d7, 0x1d8, 0xc, 0x5, 
    0x2, 0x2, 0x1d8, 0x1da, 0x7, 0x22, 0x2, 0x2, 0x1d9, 0x1db, 0x5, 0x70, 
    0x39, 0x2, 0x1da, 0x1d9, 0x3, 0x2, 0x2, 0x2, 0x1da, 0x1db, 0x3, 0x2, 
    0x2, 0x2, 0x1db, 0x1dc, 0x3, 0x2, 0x2, 0x2, 0x1dc, 0x1de, 0x7, 0x23, 
    0x2, 0x2, 0x1dd, 0x1d7, 0x3, 0x2, 0x2, 0x2, 0x1de, 0x1e1, 0x3, 0x2, 
    0x2, 0x2, 0x1df, 0x1dd, 0x3, 0x2, 0x2, 0x2, 0x1df, 0x1e0, 0x3, 0x2, 
    0x2, 0x2, 0x1e0, 0x41, 0x3, 0x2, 0x2, 0x2, 0x1e1, 0x1df, 0x3, 0x2, 0x2, 
    0x2, 0x1e2, 0x1e7, 0x5, 0xa8, 0x55, 0x2, 0x1e3, 0x1e4, 0x7, 0x25, 0x2, 
    0x2, 0x1e4, 0x1e6, 0x5, 0xa8, 0x55, 0x2, 0x1e5, 0x1e3, 0x3, 0x2, 0x2, 
    0x2, 0x1e6, 0x1e9, 0x3, 0x2, 0x2, 0x2, 0x1e7, 0x1e5, 0x3, 0x2, 0x2, 
    0x2, 0x1e7, 0x1e8, 0x3, 0x2, 0x2, 0x2, 0x1e8, 0x43, 0x3, 0x2, 0x2, 0x2, 
    0x1e9, 0x1e7, 0x3, 0x2, 0x2, 0x2, 0x1ea, 0x1eb, 0x7, 0x26, 0x2, 0x2, 
    0x1eb, 0x1ec, 0x7, 0x17, 0x2, 0x2, 0x1ec, 0x1ed, 0x5, 0x6e, 0x38, 0x2, 
    0x1ed, 0x1ee, 0x7, 0x27, 0x2, 0x2, 0x1ee, 0x1ef, 0x5, 0x40, 0x21, 0x2, 
    0x1ef, 0x1f0, 0x7, 0x18, 0x2, 0x2, 0x1f0, 0x45, 0x3, 0x2, 0x2, 0x2, 
    0x1f1, 0x1f2, 0x7, 0x1e, 0x2, 0x2, 0x1f2, 0x1f8, 0x5, 0x3a, 0x1e, 0x2, 
    0x1f3, 0x1f7, 0x7, 0x6f, 0x2, 0x2, 0x1f4, 0x1f7, 0x7, 0x6d, 0x2, 0x2, 
    0x1f5, 0x1f7, 0x5, 0x4a, 0x26, 0x2, 0x1f6, 0x1f3, 0x3, 0x2, 0x2, 0x2, 
    0x1f6, 0x1f4, 0x3, 0x2, 0x2, 0x2, 0x1f6, 0x1f5, 0x3, 0x2, 0x2, 0x2, 
    0x1f7, 0x1fa, 0x3, 0x2, 0x2, 0x2, 0x1f8, 0x1f6, 0x3, 0x2, 0x2, 0x2, 
    0x1f8, 0x1f9, 0x3, 0x2, 0x2, 0x2, 0x1f9, 0x1fd, 0x3, 0x2, 0x2, 0x2, 
    0x1fa, 0x1f8, 0x3, 0x2, 0x2, 0x2, 0x1fb, 0x1fc, 0x7, 0x1f, 0x2, 0x2, 
    0x1fc, 0x1fe, 0x5, 0x3a, 0x1e, 0x2, 0x1fd, 0x1fb, 0x3, 0x2, 0x2, 0x2, 
    0x1fd, 0x1fe, 0x3, 0x2, 0x2, 0x2, 0x1fe, 0x47, 0x3, 0x2, 0x2, 0x2, 0x1ff, 
    0x200, 0x9, 0x5, 0x2, 0x2, 0x200, 0x49, 0x3, 0x2, 0x2, 0x2, 0x201, 0x202, 
    0x9, 0x6, 0x2, 0x2, 0x202, 0x4b, 0x3, 0x2, 0x2, 0x2, 0x203, 0x207, 0x7, 
    0x10, 0x2, 0x2, 0x204, 0x206, 0x5, 0x4e, 0x28, 0x2, 0x205, 0x204, 0x3, 
    0x2, 0x2, 0x2, 0x206, 0x209, 0x3, 0x2, 0x2, 0x2, 0x207, 0x205, 0x3, 
    0x2, 0x2, 0x2, 0x207, 0x208, 0x3, 0x2, 0x2, 0x2, 0x208, 0x20a, 0x3, 
    0x2, 0x2, 0x2, 0x209, 0x207, 0x3, 0x2, 0x2, 0x2, 0x20a, 0x20b, 0x7, 
    0x12, 0x2, 0x2, 0x20b, 0x4d, 0x3, 0x2, 0x2, 0x2, 0x20c, 0x219, 0x5, 
    0x52, 0x2a, 0x2, 0x20d, 0x219, 0x5, 0x54, 0x2b, 0x2, 0x20e, 0x219, 0x5, 
    0x58, 0x2d, 0x2, 0x20f, 0x219, 0x5, 0x4c, 0x27, 0x2, 0x210, 0x219, 0x5, 
    0x5a, 0x2e, 0x2, 0x211, 0x219, 0x5, 0x5c, 0x2f, 0x2, 0x212, 0x219, 0x5, 
    0x5e, 0x30, 0x2, 0x213, 0x219, 0x5, 0x60, 0x31, 0x2, 0x214, 0x219, 0x5, 
    0x62, 0x32, 0x2, 0x215, 0x219, 0x5, 0x64, 0x33, 0x2, 0x216, 0x219, 0x5, 
    0x66, 0x34, 0x2, 0x217, 0x219, 0x5, 0x56, 0x2c, 0x2, 0x218, 0x20c, 0x3, 
    0x2, 0x2, 0x2, 0x218, 0x20d, 0x3, 0x2, 0x2, 0x2, 0x218, 0x20e, 0x3, 
    0x2, 0x2, 0x2, 0x218, 0x20f, 0x3, 0x2, 0x2, 0x2, 0x218, 0x210, 0x3, 
    0x2, 0x2, 0x2, 0x218, 0x211, 0x3, 0x2, 0x2, 0x2, 0x218, 0x212, 0x3, 
    0x2, 0x2, 0x2, 0x218, 0x213, 0x3, 0x2, 0x2, 0x2, 0x218, 0x214, 0x3, 
    0x2, 0x2, 0x2, 0x218, 0x215, 0x3, 0x2, 0x2, 0x2, 0x218, 0x216, 0x3, 
    0x2, 0x2, 0x2, 0x218, 0x217, 0x3, 0x2, 0x2, 0x2, 0x219, 0x4f, 0x3, 0x2, 
    0x2, 0x2, 0x21a, 0x21b, 0x5, 0x70, 0x39, 0x2, 0x21b, 0x21c, 0x7, 0x4, 
    0x2, 0x2, 0x21c, 0x51, 0x3, 0x2, 0x2, 0x2, 0x21d, 0x21e, 0x7, 0x2b, 
    0x2, 0x2, 0x21e, 0x21f, 0x7, 0x17, 0x2, 0x2, 0x21f, 0x220, 0x5, 0x70, 
    0x39, 0x2, 0x220, 0x221, 0x7, 0x18, 0x2, 0x2, 0x221, 0x224, 0x5, 0x4e, 
    0x28, 0x2, 0x222, 0x223, 0x7, 0x2c, 0x2, 0x2, 0x223, 0x225, 0x5, 0x4e, 
    0x28, 0x2, 0x224, 0x222, 0x3, 0x2, 0x2, 0x2, 0x224, 0x225, 0x3, 0x2, 
    0x2, 0x2, 0x225, 0x53, 0x3, 0x2, 0x2, 0x2, 0x226, 0x227, 0x7, 0x2d, 
    0x2, 0x2, 0x227, 0x228, 0x7, 0x17, 0x2, 0x2, 0x228, 0x229, 0x5, 0x70, 
    0x39, 0x2, 0x229, 0x22a, 0x7, 0x18, 0x2, 0x2, 0x22a, 0x22b, 0x5, 0x4e, 
    0x28, 0x2, 0x22b, 0x55, 0x3, 0x2, 0x2, 0x2, 0x22c, 0x22f, 0x5, 0x68, 
    0x35, 0x2, 0x22d, 0x22f, 0x5, 0x50, 0x29, 0x2, 0x22e, 0x22c, 0x3, 0x2, 
    0x2, 0x2, 0x22e, 0x22d, 0x3, 0x2, 0x2, 0x2, 0x22f, 0x57, 0x3, 0x2, 0x2, 
    0x2, 0x230, 0x231, 0x7, 0x1a, 0x2, 0x2, 0x231, 0x234, 0x7, 0x17, 0x2, 
    0x2, 0x232, 0x235, 0x5, 0x56, 0x2c, 0x2, 0x233, 0x235, 0x7, 0x4, 0x2, 
    0x2, 0x234, 0x232, 0x3, 0x2, 0x2, 0x2, 0x234, 0x233, 0x3, 0x2, 0x2, 
    0x2, 0x235, 0x238, 0x3, 0x2, 0x2, 0x2, 0x236, 0x239, 0x5, 0x50, 0x29, 
    0x2, 0x237, 0x239, 0x7, 0x4, 0x2, 0x2, 0x238, 0x236, 0x3, 0x2, 0x2, 
    0x2, 0x238, 0x237, 0x3, 0x2, 0x2, 0x2, 0x239, 0x23b, 0x3, 0x2, 0x2, 
    0x2, 0x23a, 0x23c, 0x5, 0x70, 0x39, 0x2, 0x23b, 0x23a, 0x3, 0x2, 0x2, 
    0x2, 0x23b, 0x23c, 0x3, 0x2, 0x2, 0x2, 0x23c, 0x23d, 0x3, 0x2, 0x2, 
    0x2, 0x23d, 0x23e, 0x7, 0x18, 0x2, 0x2, 0x23e, 0x23f, 0x5, 0x4e, 0x28, 
    0x2, 0x23f, 0x59, 0x3, 0x2, 0x2, 0x2, 0x240, 0x242, 0x7, 0x2e, 0x2, 
    0x2, 0x241, 0x243, 0x7, 0x76, 0x2, 0x2, 0x242, 0x241, 0x3, 0x2, 0x2, 
    0x2, 0x242, 0x243, 0x3, 0x2, 0x2, 0x2, 0x243, 0x244, 0x3, 0x2, 0x2, 
    0x2, 0x244, 0x245, 0x5, 0x7e, 0x40, 0x2, 0x245, 0x5b, 0x3, 0x2, 0x2, 
    0x2, 0x246, 0x247, 0x7, 0x2f, 0x2, 0x2, 0x247, 0x248, 0x5, 0x4e, 0x28, 
    0x2, 0x248, 0x249, 0x7, 0x2d, 0x2, 0x2, 0x249, 0x24a, 0x7, 0x17, 0x2, 
    0x2, 0x24a, 0x24b, 0x5, 0x70, 0x39, 0x2, 0x24b, 0x24c, 0x7, 0x18, 0x2, 
    0x2, 0x24c, 0x24d, 0x7, 0x4, 0x2, 0x2, 0x24d, 0x5d, 0x3, 0x2, 0x2, 0x2, 
    0x24e, 0x24f, 0x7, 0x6c, 0x2, 0x2, 0x24f, 0x250, 0x7, 0x4, 0x2, 0x2, 
    0x250, 0x5f, 0x3, 0x2, 0x2, 0x2, 0x251, 0x252, 0x7, 0x6a, 0x2, 0x2, 
    0x252, 0x253, 0x7, 0x4, 0x2, 0x2, 0x253, 0x61, 0x3, 0x2, 0x2, 0x2, 0x254, 
    0x256, 0x7, 0x30, 0x2, 0x2, 0x255, 0x257, 0x5, 0x70, 0x39, 0x2, 0x256, 
    0x255, 0x3, 0x2, 0x2, 0x2, 0x256, 0x257, 0x3, 0x2, 0x2, 0x2, 0x257, 
    0x258, 0x3, 0x2, 0x2, 0x2, 0x258, 0x259, 0x7, 0x4, 0x2, 0x2, 0x259, 
    0x63, 0x3, 0x2, 0x2, 0x2, 0x25a, 0x25b, 0x7, 0x31, 0x2, 0x2, 0x25b, 
    0x25c, 0x7, 0x4, 0x2, 0x2, 0x25c, 0x65, 0x3, 0x2, 0x2, 0x2, 0x25d, 0x25e, 
    0x7, 0x32, 0x2, 0x2, 0x25e, 0x25f, 0x5, 0x7c, 0x3f, 0x2, 0x25f, 0x260, 
    0x7, 0x4, 0x2, 0x2, 0x260, 0x67, 0x3, 0x2, 0x2, 0x2, 0x261, 0x262, 0x7, 
    0x33, 0x2, 0x2, 0x262, 0x269, 0x5, 0x6c, 0x37, 0x2, 0x263, 0x269, 0x5, 
    0x3e, 0x20, 0x2, 0x264, 0x265, 0x7, 0x17, 0x2, 0x2, 0x265, 0x266, 0x5, 
    0x6a, 0x36, 0x2, 0x266, 0x267, 0x7, 0x18, 0x2, 0x2, 0x267, 0x269, 0x3, 
    0x2, 0x2, 0x2, 0x268, 0x261, 0x3, 0x2, 0x2, 0x2, 0x268, 0x263, 0x3, 
    0x2, 0x2, 0x2, 0x268, 0x264, 0x3, 0x2, 0x2, 0x2, 0x269, 0x26c, 0x3, 
    0x2, 0x2, 0x2, 0x26a, 0x26b, 0x7, 0xb, 0x2, 0x2, 0x26b, 0x26d, 0x5, 
    0x70, 0x39, 0x2, 0x26c, 0x26a, 0x3, 0x2, 0x2, 0x2, 0x26c, 0x26d, 0x3, 
    0x2, 0x2, 0x2, 0x26d, 0x26e, 0x3, 0x2, 0x2, 0x2, 0x26e, 0x26f, 0x7, 
    0x4, 0x2, 0x2, 0x26f, 0x69, 0x3, 0x2, 0x2, 0x2, 0x270, 0x272, 0x5, 0x3e, 
    0x20, 0x2, 0x271, 0x270, 0x3, 0x2, 0x2, 0x2, 0x271, 0x272, 0x3, 0x2, 
    0x2, 0x2, 0x272, 0x279, 0x3, 0x2, 0x2, 0x2, 0x273, 0x275, 0x7, 0x11, 
    0x2, 0x2, 0x274, 0x276, 0x5, 0x3e, 0x20, 0x2, 0x275, 0x274, 0x3, 0x2, 
    0x2, 0x2, 0x275, 0x276, 0x3, 0x2, 0x2, 0x2, 0x276, 0x278, 0x3, 0x2, 
    0x2, 0x2, 0x277, 0x273, 0x3, 0x2, 0x2, 0x2, 0x278, 0x27b, 0x3, 0x2, 
    0x2, 0x2, 0x279, 0x277, 0x3, 0x2, 0x2, 0x2, 0x279, 0x27a, 0x3, 0x2, 
    0x2, 0x2, 0x27a, 0x6b, 0x3, 0x2, 0x2, 0x2, 0x27b, 0x279, 0x3, 0x2, 0x2, 
    0x2, 0x27c, 0x283, 0x7, 0x17, 0x2, 0x2, 0x27d, 0x27f, 0x5, 0xa8, 0x55, 
    0x2, 0x27e, 0x27d, 0x3, 0x2, 0x2, 0x2, 0x27e, 0x27f, 0x3, 0x2, 0x2, 
    0x2, 0x27f, 0x280, 0x3, 0x2, 0x2, 0x2, 0x280, 0x282, 0x7, 0x11, 0x2, 
    0x2, 0x281, 0x27e, 0x3, 0x2, 0x2, 0x2, 0x282, 0x285, 0x3, 0x2, 0x2, 
    0x2, 0x283, 0x281, 0x3, 0x2, 0x2, 0x2, 0x283, 0x284, 0x3, 0x2, 0x2, 
    0x2, 0x284, 0x287, 0x3, 0x2, 0x2, 0x2, 0x285, 0x283, 0x3, 0x2, 0x2, 
    0x2, 0x286, 0x288, 0x5, 0xa8, 0x55, 0x2, 0x287, 0x286, 0x3, 0x2, 0x2, 
    0x2, 0x287, 0x288, 0x3, 0x2, 0x2, 0x2, 0x288, 0x289, 0x3, 0x2, 0x2, 
    0x2, 0x289, 0x28a, 0x7, 0x18, 0x2, 0x2, 0x28a, 0x6d, 0x3, 0x2, 0x2, 
    0x2, 0x28b, 0x28c, 0x9, 0x7, 0x2, 0x2, 0x28c, 0x6f, 0x3, 0x2, 0x2, 0x2, 
    0x28d, 0x28e, 0x8, 0x39, 0x1, 0x2, 0x28e, 0x28f, 0x7, 0x39, 0x2, 0x2, 
    0x28f, 0x2a0, 0x5, 0x40, 0x21, 0x2, 0x290, 0x291, 0x7, 0x17, 0x2, 0x2, 
    0x291, 0x292, 0x5, 0x70, 0x39, 0x2, 0x292, 0x293, 0x7, 0x18, 0x2, 0x2, 
    0x293, 0x2a0, 0x3, 0x2, 0x2, 0x2, 0x294, 0x295, 0x9, 0x8, 0x2, 0x2, 
    0x295, 0x2a0, 0x5, 0x70, 0x39, 0x15, 0x296, 0x297, 0x9, 0x9, 0x2, 0x2, 
    0x297, 0x2a0, 0x5, 0x70, 0x39, 0x14, 0x298, 0x299, 0x9, 0xa, 0x2, 0x2, 
    0x299, 0x2a0, 0x5, 0x70, 0x39, 0x13, 0x29a, 0x29b, 0x7, 0x3e, 0x2, 0x2, 
    0x29b, 0x2a0, 0x5, 0x70, 0x39, 0x12, 0x29c, 0x29d, 0x7, 0x6, 0x2, 0x2, 
    0x29d, 0x2a0, 0x5, 0x70, 0x39, 0x11, 0x29e, 0x2a0, 0x5, 0x72, 0x3a, 
    0x2, 0x29f, 0x28d, 0x3, 0x2, 0x2, 0x2, 0x29f, 0x290, 0x3, 0x2, 0x2, 
    0x2, 0x29f, 0x294, 0x3, 0x2, 0x2, 0x2, 0x29f, 0x296, 0x3, 0x2, 0x2, 
    0x2, 0x29f, 0x298, 0x3, 0x2, 0x2, 0x2, 0x29f, 0x29a, 0x3, 0x2, 0x2, 
    0x2, 0x29f, 0x29c, 0x3, 0x2, 0x2, 0x2, 0x29f, 0x29e, 0x3, 0x2, 0x2, 
    0x2, 0x2a0, 0x2dc, 0x3, 0x2, 0x2, 0x2, 0x2a1, 0x2a2, 0xc, 0x10, 0x2, 
    0x2, 0x2a2, 0x2a3, 0x7, 0x3f, 0x2, 0x2, 0x2a3, 0x2db, 0x5, 0x70, 0x39, 
    0x11, 0x2a4, 0x2a5, 0xc, 0xf, 0x2, 0x2, 0x2a5, 0x2a6, 0x9, 0xb, 0x2, 
    0x2, 0x2a6, 0x2db, 0x5, 0x70, 0x39, 0x10, 0x2a7, 0x2a8, 0xc, 0xe, 0x2, 
    0x2, 0x2a8, 0x2a9, 0x9, 0x9, 0x2, 0x2, 0x2a9, 0x2db, 0x5, 0x70, 0x39, 
    0xf, 0x2aa, 0x2ab, 0xc, 0xd, 0x2, 0x2, 0x2ab, 0x2ac, 0x9, 0xc, 0x2, 
    0x2, 0x2ac, 0x2db, 0x5, 0x70, 0x39, 0xe, 0x2ad, 0x2ae, 0xc, 0xc, 0x2, 
    0x2, 0x2ae, 0x2af, 0x7, 0x44, 0x2, 0x2, 0x2af, 0x2db, 0x5, 0x70, 0x39, 
    0xd, 0x2b0, 0x2b1, 0xc, 0xb, 0x2, 0x2, 0x2b1, 0x2b2, 0x7, 0x5, 0x2, 
    0x2, 0x2b2, 0x2db, 0x5, 0x70, 0x39, 0xc, 0x2b3, 0x2b4, 0xc, 0xa, 0x2, 
    0x2, 0x2b4, 0x2b5, 0x7, 0x45, 0x2, 0x2, 0x2b5, 0x2db, 0x5, 0x70, 0x39, 
    0xb, 0x2b6, 0x2b7, 0xc, 0x9, 0x2, 0x2, 0x2b7, 0x2b8, 0x9, 0xd, 0x2, 
    0x2, 0x2b8, 0x2db, 0x5, 0x70, 0x39, 0xa, 0x2b9, 0x2ba, 0xc, 0x8, 0x2, 
    0x2, 0x2ba, 0x2bb, 0x9, 0xe, 0x2, 0x2, 0x2bb, 0x2db, 0x5, 0x70, 0x39, 
    0x9, 0x2bc, 0x2bd, 0xc, 0x7, 0x2, 0x2, 0x2bd, 0x2be, 0x7, 0x48, 0x2, 
    0x2, 0x2be, 0x2db, 0x5, 0x70, 0x39, 0x8, 0x2bf, 0x2c0, 0xc, 0x6, 0x2, 
    0x2, 0x2c0, 0x2c1, 0x7, 0x49, 0x2, 0x2, 0x2c1, 0x2db, 0x5, 0x70, 0x39, 
    0x7, 0x2c2, 0x2c3, 0xc, 0x5, 0x2, 0x2, 0x2c3, 0x2c4, 0x7, 0x4a, 0x2, 
    0x2, 0x2c4, 0x2c5, 0x5, 0x70, 0x39, 0x2, 0x2c5, 0x2c6, 0x7, 0x4b, 0x2, 
    0x2, 0x2c6, 0x2c7, 0x5, 0x70, 0x39, 0x6, 0x2c7, 0x2db, 0x3, 0x2, 0x2, 
    0x2, 0x2c8, 0x2c9, 0xc, 0x4, 0x2, 0x2, 0x2c9, 0x2ca, 0x9, 0xf, 0x2, 
    0x2, 0x2ca, 0x2db, 0x5, 0x70, 0x39, 0x5, 0x2cb, 0x2cc, 0xc, 0x1b, 0x2, 
    0x2, 0x2cc, 0x2db, 0x9, 0x8, 0x2, 0x2, 0x2cd, 0x2ce, 0xc, 0x19, 0x2, 
    0x2, 0x2ce, 0x2cf, 0x7, 0x22, 0x2, 0x2, 0x2cf, 0x2d0, 0x5, 0x70, 0x39, 
    0x2, 0x2d0, 0x2d1, 0x7, 0x23, 0x2, 0x2, 0x2d1, 0x2db, 0x3, 0x2, 0x2, 
    0x2, 0x2d2, 0x2d3, 0xc, 0x18, 0x2, 0x2, 0x2d3, 0x2d4, 0x7, 0x17, 0x2, 
    0x2, 0x2d4, 0x2d5, 0x5, 0x7a, 0x3e, 0x2, 0x2d5, 0x2d6, 0x7, 0x18, 0x2, 
    0x2, 0x2d6, 0x2db, 0x3, 0x2, 0x2, 0x2, 0x2d7, 0x2d8, 0xc, 0x17, 0x2, 
    0x2, 0x2d8, 0x2d9, 0x7, 0x25, 0x2, 0x2, 0x2d9, 0x2db, 0x5, 0xa8, 0x55, 
    0x2, 0x2da, 0x2a1, 0x3, 0x2, 0x2, 0x2, 0x2da, 0x2a4, 0x3, 0x2, 0x2, 
    0x2, 0x2da, 0x2a7, 0x3, 0x2, 0x2, 0x2, 0x2da, 0x2aa, 0x3, 0x2, 0x2, 
    0x2, 0x2da, 0x2ad, 0x3, 0x2, 0x2, 0x2, 0x2da, 0x2b0, 0x3, 0x2, 0x2, 
    0x2, 0x2da, 0x2b3, 0x3, 0x2, 0x2, 0x2, 0x2da, 0x2b6, 0x3, 0x2, 0x2, 
    0x2, 0x2da, 0x2b9, 0x3, 0x2, 0x2, 0x2, 0x2da, 0x2bc, 0x3, 0x2, 0x2, 
    0x2, 0x2da, 0x2bf, 0x3, 0x2, 0x2, 0x2, 0x2da, 0x2c2, 0x3, 0x2, 0x2, 
    0x2, 0x2da, 0x2c8, 0x3, 0x2, 0x2, 0x2, 0x2da, 0x2cb, 0x3, 0x2, 0x2, 
    0x2, 0x2da, 0x2cd, 0x3, 0x2, 0x2, 0x2, 0x2da, 0x2d2, 0x3, 0x2, 0x2, 
    0x2, 0x2da, 0x2d7, 0x3, 0x2, 0x2, 0x2, 0x2db, 0x2de, 0x3, 0x2, 0x2, 
    0x2, 0x2dc, 0x2da, 0x3, 0x2, 0x2, 0x2, 0x2dc, 0x2dd, 0x3, 0x2, 0x2, 
    0x2, 0x2dd, 0x71, 0x3, 0x2, 0x2, 0x2, 0x2de, 0x2dc, 0x3, 0x2, 0x2, 0x2, 
    0x2df, 0x2ef, 0x7, 0x63, 0x2, 0x2, 0x2e0, 0x2ef, 0x5, 0xa6, 0x54, 0x2, 
    0x2e1, 0x2ef, 0x7, 0x67, 0x2, 0x2, 0x2e2, 0x2ef, 0x7, 0x76, 0x2, 0x2, 
    0x2e3, 0x2e6, 0x5, 0xa8, 0x55, 0x2, 0x2e4, 0x2e5, 0x7, 0x22, 0x2, 0x2, 
    0x2e5, 0x2e7, 0x7, 0x23, 0x2, 0x2, 0x2e6, 0x2e4, 0x3, 0x2, 0x2, 0x2, 
    0x2e6, 0x2e7, 0x3, 0x2, 0x2, 0x2, 0x2e7, 0x2ef, 0x3, 0x2, 0x2, 0x2, 
    0x2e8, 0x2ef, 0x5, 0xa2, 0x52, 0x2, 0x2e9, 0x2ec, 0x5, 0xa4, 0x53, 0x2, 
    0x2ea, 0x2eb, 0x7, 0x22, 0x2, 0x2, 0x2eb, 0x2ed, 0x7, 0x23, 0x2, 0x2, 
    0x2ec, 0x2ea, 0x3, 0x2, 0x2, 0x2, 0x2ec, 0x2ed, 0x3, 0x2, 0x2, 0x2, 
    0x2ed, 0x2ef, 0x3, 0x2, 0x2, 0x2, 0x2ee, 0x2df, 0x3, 0x2, 0x2, 0x2, 
    0x2ee, 0x2e0, 0x3, 0x2, 0x2, 0x2, 0x2ee, 0x2e1, 0x3, 0x2, 0x2, 0x2, 
    0x2ee, 0x2e2, 0x3, 0x2, 0x2, 0x2, 0x2ee, 0x2e3, 0x3, 0x2, 0x2, 0x2, 
    0x2ee, 0x2e8, 0x3, 0x2, 0x2, 0x2, 0x2ee, 0x2e9, 0x3, 0x2, 0x2, 0x2, 
    0x2ef, 0x73, 0x3, 0x2, 0x2, 0x2, 0x2f0, 0x2f5, 0x5, 0x70, 0x39, 0x2, 
    0x2f1, 0x2f2, 0x7, 0x11, 0x2, 0x2, 0x2f2, 0x2f4, 0x5, 0x70, 0x39, 0x2, 
    0x2f3, 0x2f1, 0x3, 0x2, 0x2, 0x2, 0x2f4, 0x2f7, 0x3, 0x2, 0x2, 0x2, 
    0x2f5, 0x2f3, 0x3, 0x2, 0x2, 0x2, 0x2f5, 0x2f6, 0x3, 0x2, 0x2, 0x2, 
    0x2f6, 0x75, 0x3, 0x2, 0x2, 0x2, 0x2f7, 0x2f5, 0x3, 0x2, 0x2, 0x2, 0x2f8, 
    0x2fd, 0x5, 0x78, 0x3d, 0x2, 0x2f9, 0x2fa, 0x7, 0x11, 0x2, 0x2, 0x2fa, 
    0x2fc, 0x5, 0x78, 0x3d, 0x2, 0x2fb, 0x2f9, 0x3, 0x2, 0x2, 0x2, 0x2fc, 
    0x2ff, 0x3, 0x2, 0x2, 0x2, 0x2fd, 0x2fb, 0x3, 0x2, 0x2, 0x2, 0x2fd, 
    0x2fe, 0x3, 0x2, 0x2, 0x2, 0x2fe, 0x301, 0x3, 0x2, 0x2, 0x2, 0x2ff, 
    0x2fd, 0x3, 0x2, 0x2, 0x2, 0x300, 0x302, 0x7, 0x11, 0x2, 0x2, 0x301, 
    0x300, 0x3, 0x2, 0x2, 0x2, 0x301, 0x302, 0x3, 0x2, 0x2, 0x2, 0x302, 
    0x77, 0x3, 0x2, 0x2, 0x2, 0x303, 0x304, 0x5, 0xa8, 0x55, 0x2, 0x304, 
    0x305, 0x7, 0x4b, 0x2, 0x2, 0x305, 0x306, 0x5, 0x70, 0x39, 0x2, 0x306, 
    0x79, 0x3, 0x2, 0x2, 0x2, 0x307, 0x309, 0x7, 0x10, 0x2, 0x2, 0x308, 
    0x30a, 0x5, 0x76, 0x3c, 0x2, 0x309, 0x308, 0x3, 0x2, 0x2, 0x2, 0x309, 
    0x30a, 0x3, 0x2, 0x2, 0x2, 0x30a, 0x30b, 0x3, 0x2, 0x2, 0x2, 0x30b, 
    0x310, 0x7, 0x12, 0x2, 0x2, 0x30c, 0x30e, 0x5, 0x74, 0x3b, 0x2, 0x30d, 
    0x30c, 0x3, 0x2, 0x2, 0x2, 0x30d, 0x30e, 0x3, 0x2, 0x2, 0x2, 0x30e, 
    0x310, 0x3, 0x2, 0x2, 0x2, 0x30f, 0x307, 0x3, 0x2, 0x2, 0x2, 0x30f, 
    0x30d, 0x3, 0x2, 0x2, 0x2, 0x310, 0x7b, 0x3, 0x2, 0x2, 0x2, 0x311, 0x312, 
    0x5, 0x70, 0x39, 0x2, 0x312, 0x313, 0x7, 0x17, 0x2, 0x2, 0x313, 0x314, 
    0x5, 0x7a, 0x3e, 0x2, 0x314, 0x315, 0x7, 0x18, 0x2, 0x2, 0x315, 0x7d, 
    0x3, 0x2, 0x2, 0x2, 0x316, 0x31a, 0x7, 0x10, 0x2, 0x2, 0x317, 0x319, 
    0x5, 0x80, 0x41, 0x2, 0x318, 0x317, 0x3, 0x2, 0x2, 0x2, 0x319, 0x31c, 
    0x3, 0x2, 0x2, 0x2, 0x31a, 0x318, 0x3, 0x2, 0x2, 0x2, 0x31a, 0x31b, 
    0x3, 0x2, 0x2, 0x2, 0x31b, 0x31d, 0x3, 0x2, 0x2, 0x2, 0x31c, 0x31a, 
    0x3, 0x2, 0x2, 0x2, 0x31d, 0x31e, 0x7, 0x12, 0x2, 0x2, 0x31e, 0x7f, 
    0x3, 0x2, 0x2, 0x2, 0x31f, 0x331, 0x5, 0xa8, 0x55, 0x2, 0x320, 0x331, 
    0x5, 0x7e, 0x40, 0x2, 0x321, 0x331, 0x5, 0x82, 0x42, 0x2, 0x322, 0x331, 
    0x5, 0x86, 0x44, 0x2, 0x323, 0x331, 0x5, 0x88, 0x45, 0x2, 0x324, 0x331, 
    0x5, 0x8e, 0x48, 0x2, 0x325, 0x331, 0x5, 0x90, 0x49, 0x2, 0x326, 0x331, 
    0x5, 0x92, 0x4a, 0x2, 0x327, 0x331, 0x5, 0x96, 0x4c, 0x2, 0x328, 0x331, 
    0x5, 0x9a, 0x4e, 0x2, 0x329, 0x331, 0x5, 0x9c, 0x4f, 0x2, 0x32a, 0x331, 
    0x7, 0x6a, 0x2, 0x2, 0x32b, 0x331, 0x7, 0x6c, 0x2, 0x2, 0x32c, 0x331, 
    0x5, 0xa0, 0x51, 0x2, 0x32d, 0x331, 0x5, 0xa6, 0x54, 0x2, 0x32e, 0x331, 
    0x7, 0x76, 0x2, 0x2, 0x32f, 0x331, 0x7, 0x67, 0x2, 0x2, 0x330, 0x31f, 
    0x3, 0x2, 0x2, 0x2, 0x330, 0x320, 0x3, 0x2, 0x2, 0x2, 0x330, 0x321, 
    0x3, 0x2, 0x2, 0x2, 0x330, 0x322, 0x3, 0x2, 0x2, 0x2, 0x330, 0x323, 
    0x3, 0x2, 0x2, 0x2, 0x330, 0x324, 0x3, 0x2, 0x2, 0x2, 0x330, 0x325, 
    0x3, 0x2, 0x2, 0x2, 0x330, 0x326, 0x3, 0x2, 0x2, 0x2, 0x330, 0x327, 
    0x3, 0x2, 0x2, 0x2, 0x330, 0x328, 0x3, 0x2, 0x2, 0x2, 0x330, 0x329, 
    0x3, 0x2, 0x2, 0x2, 0x330, 0x32a, 0x3, 0x2, 0x2, 0x2, 0x330, 0x32b, 
    0x3, 0x2, 0x2, 0x2, 0x330, 0x32c, 0x3, 0x2, 0x2, 0x2, 0x330, 0x32d, 
    0x3, 0x2, 0x2, 0x2, 0x330, 0x32e, 0x3, 0x2, 0x2, 0x2, 0x330, 0x32f, 
    0x3, 0x2, 0x2, 0x2, 0x331, 0x81, 0x3, 0x2, 0x2, 0x2, 0x332, 0x335, 0x5, 
    0x84, 0x43, 0x2, 0x333, 0x335, 0x5, 0x9e, 0x50, 0x2, 0x334, 0x332, 0x3, 
    0x2, 0x2, 0x2, 0x334, 0x333, 0x3, 0x2, 0x2, 0x2, 0x335, 0x83, 0x3, 0x2, 
    0x2, 0x2, 0x336, 0x33b, 0x7, 0x30, 0x2, 0x2, 0x337, 0x33b, 0x7, 0x24, 
    0x2, 0x2, 0x338, 0x33b, 0x7, 0x36, 0x2, 0x2, 0x339, 0x33b, 0x5, 0xa8, 
    0x55, 0x2, 0x33a, 0x336, 0x3, 0x2, 0x2, 0x2, 0x33a, 0x337, 0x3, 0x2, 
    0x2, 0x2, 0x33a, 0x338, 0x3, 0x2, 0x2, 0x2, 0x33a, 0x339, 0x3, 0x2, 
    0x2, 0x2, 0x33b, 0x348, 0x3, 0x2, 0x2, 0x2, 0x33c, 0x33e, 0x7, 0x17, 
    0x2, 0x2, 0x33d, 0x33f, 0x5, 0x82, 0x42, 0x2, 0x33e, 0x33d, 0x3, 0x2, 
    0x2, 0x2, 0x33e, 0x33f, 0x3, 0x2, 0x2, 0x2, 0x33f, 0x344, 0x3, 0x2, 
    0x2, 0x2, 0x340, 0x341, 0x7, 0x11, 0x2, 0x2, 0x341, 0x343, 0x5, 0x82, 
    0x42, 0x2, 0x342, 0x340, 0x3, 0x2, 0x2, 0x2, 0x343, 0x346, 0x3, 0x2, 
    0x2, 0x2, 0x344, 0x342, 0x3, 0x2, 0x2, 0x2, 0x344, 0x345, 0x3, 0x2, 
    0x2, 0x2, 0x345, 0x347, 0x3, 0x2, 0x2, 0x2, 0x346, 0x344, 0x3, 0x2, 
    0x2, 0x2, 0x347, 0x349, 0x7, 0x18, 0x2, 0x2, 0x348, 0x33c, 0x3, 0x2, 
    0x2, 0x2, 0x348, 0x349, 0x3, 0x2, 0x2, 0x2, 0x349, 0x85, 0x3, 0x2, 0x2, 
    0x2, 0x34a, 0x34b, 0x7, 0x56, 0x2, 0x2, 0x34b, 0x34e, 0x5, 0x8a, 0x46, 
    0x2, 0x34c, 0x34d, 0x7, 0x57, 0x2, 0x2, 0x34d, 0x34f, 0x5, 0x82, 0x42, 
    0x2, 0x34e, 0x34c, 0x3, 0x2, 0x2, 0x2, 0x34e, 0x34f, 0x3, 0x2, 0x2, 
    0x2, 0x34f, 0x87, 0x3, 0x2, 0x2, 0x2, 0x350, 0x351, 0x5, 0x8a, 0x46, 
    0x2, 0x351, 0x352, 0x7, 0x57, 0x2, 0x2, 0x352, 0x353, 0x5, 0x82, 0x42, 
    0x2, 0x353, 0x89, 0x3, 0x2, 0x2, 0x2, 0x354, 0x35a, 0x5, 0xa8, 0x55, 
    0x2, 0x355, 0x356, 0x7, 0x17, 0x2, 0x2, 0x356, 0x357, 0x5, 0x8c, 0x47, 
    0x2, 0x357, 0x358, 0x7, 0x18, 0x2, 0x2, 0x358, 0x35a, 0x3, 0x2, 0x2, 
    0x2, 0x359, 0x354, 0x3, 0x2, 0x2, 0x2, 0x359, 0x355, 0x3, 0x2, 0x2, 
    0x2, 0x35a, 0x8b, 0x3, 0x2, 0x2, 0x2, 0x35b, 0x360, 0x5, 0xa8, 0x55, 
    0x2, 0x35c, 0x35d, 0x7, 0x11, 0x2, 0x2, 0x35d, 0x35f, 0x5, 0xa8, 0x55, 
    0x2, 0x35e, 0x35c, 0x3, 0x2, 0x2, 0x2, 0x35f, 0x362, 0x3, 0x2, 0x2, 
    0x2, 0x360, 0x35e, 0x3, 0x2, 0x2, 0x2, 0x360, 0x361, 0x3, 0x2, 0x2, 
    0x2, 0x361, 0x8d, 0x3, 0x2, 0x2, 0x2, 0x362, 0x360, 0x3, 0x2, 0x2, 0x2, 
    0x363, 0x364, 0x7, 0x58, 0x2, 0x2, 0x364, 0x365, 0x5, 0xa8, 0x55, 0x2, 
    0x365, 0x8f, 0x3, 0x2, 0x2, 0x2, 0x366, 0x367, 0x5, 0xa8, 0x55, 0x2, 
    0x367, 0x368, 0x7, 0x4b, 0x2, 0x2, 0x368, 0x91, 0x3, 0x2, 0x2, 0x2, 
    0x369, 0x36a, 0x7, 0x59, 0x2, 0x2, 0x36a, 0x36e, 0x5, 0x82, 0x42, 0x2, 
    0x36b, 0x36d, 0x5, 0x94, 0x4b, 0x2, 0x36c, 0x36b, 0x3, 0x2, 0x2, 0x2, 
    0x36d, 0x370, 0x3, 0x2, 0x2, 0x2, 0x36e, 0x36c, 0x3, 0x2, 0x2, 0x2, 
    0x36e, 0x36f, 0x3, 0x2, 0x2, 0x2, 0x36f, 0x93, 0x3, 0x2, 0x2, 0x2, 0x370, 
    0x36e, 0x3, 0x2, 0x2, 0x2, 0x371, 0x372, 0x7, 0x5a, 0x2, 0x2, 0x372, 
    0x373, 0x5, 0x9e, 0x50, 0x2, 0x373, 0x374, 0x5, 0x7e, 0x40, 0x2, 0x374, 
    0x378, 0x3, 0x2, 0x2, 0x2, 0x375, 0x376, 0x7, 0x5b, 0x2, 0x2, 0x376, 
    0x378, 0x5, 0x7e, 0x40, 0x2, 0x377, 0x371, 0x3, 0x2, 0x2, 0x2, 0x377, 
    0x375, 0x3, 0x2, 0x2, 0x2, 0x378, 0x95, 0x3, 0x2, 0x2, 0x2, 0x379, 0x37a, 
    0x7, 0x1e, 0x2, 0x2, 0x37a, 0x37b, 0x5, 0xa8, 0x55, 0x2, 0x37b, 0x37d, 
    0x7, 0x17, 0x2, 0x2, 0x37c, 0x37e, 0x5, 0x8c, 0x47, 0x2, 0x37d, 0x37c, 
    0x3, 0x2, 0x2, 0x2, 0x37d, 0x37e, 0x3, 0x2, 0x2, 0x2, 0x37e, 0x37f, 
    0x3, 0x2, 0x2, 0x2, 0x37f, 0x381, 0x7, 0x18, 0x2, 0x2, 0x380, 0x382, 
    0x5, 0x98, 0x4d, 0x2, 0x381, 0x380, 0x3, 0x2, 0x2, 0x2, 0x381, 0x382, 
    0x3, 0x2, 0x2, 0x2, 0x382, 0x383, 0x3, 0x2, 0x2, 0x2, 0x383, 0x384, 
    0x5, 0x7e, 0x40, 0x2, 0x384, 0x97, 0x3, 0x2, 0x2, 0x2, 0x385, 0x386, 
    0x7, 0x5c, 0x2, 0x2, 0x386, 0x387, 0x5, 0x8c, 0x47, 0x2, 0x387, 0x99, 
    0x3, 0x2, 0x2, 0x2, 0x388, 0x38b, 0x7, 0x1a, 0x2, 0x2, 0x389, 0x38c, 
    0x5, 0x7e, 0x40, 0x2, 0x38a, 0x38c, 0x5, 0x82, 0x42, 0x2, 0x38b, 0x389, 
    0x3, 0x2, 0x2, 0x2, 0x38b, 0x38a, 0x3, 0x2, 0x2, 0x2, 0x38c, 0x38d, 
    0x3, 0x2, 0x2, 0x2, 0x38d, 0x390, 0x5, 0x82, 0x42, 0x2, 0x38e, 0x391, 
    0x5, 0x7e, 0x40, 0x2, 0x38f, 0x391, 0x5, 0x82, 0x42, 0x2, 0x390, 0x38e, 
    0x3, 0x2, 0x2, 0x2, 0x390, 0x38f, 0x3, 0x2, 0x2, 0x2, 0x391, 0x392, 
    0x3, 0x2, 0x2, 0x2, 0x392, 0x393, 0x5, 0x7e, 0x40, 0x2, 0x393, 0x9b, 
    0x3, 0x2, 0x2, 0x2, 0x394, 0x395, 0x7, 0x2b, 0x2, 0x2, 0x395, 0x396, 
    0x5, 0x82, 0x42, 0x2, 0x396, 0x397, 0x5, 0x7e, 0x40, 0x2, 0x397, 0x9d, 
    0x3, 0x2, 0x2, 0x2, 0x398, 0x399, 0x9, 0x10, 0x2, 0x2, 0x399, 0x9f, 
    0x3, 0x2, 0x2, 0x2, 0x39a, 0x39b, 0x7, 0x2e, 0x2, 0x2, 0x39b, 0x39c, 
    0x5, 0xa8, 0x55, 0x2, 0x39c, 0x39d, 0x5, 0x7e, 0x40, 0x2, 0x39d, 0xa1, 
    0x3, 0x2, 0x2, 0x2, 0x39e, 0x3a0, 0x7, 0x17, 0x2, 0x2, 0x39f, 0x3a1, 
    0x5, 0x70, 0x39, 0x2, 0x3a0, 0x39f, 0x3, 0x2, 0x2, 0x2, 0x3a0, 0x3a1, 
    0x3, 0x2, 0x2, 0x2, 0x3a1, 0x3a8, 0x3, 0x2, 0x2, 0x2, 0x3a2, 0x3a4, 
    0x7, 0x11, 0x2, 0x2, 0x3a3, 0x3a5, 0x5, 0x70, 0x39, 0x2, 0x3a4, 0x3a3, 
    0x3, 0x2, 0x2, 0x2, 0x3a4, 0x3a5, 0x3, 0x2, 0x2, 0x2, 0x3a5, 0x3a7, 
    0x3, 0x2, 0x2, 0x2, 0x3a6, 0x3a2, 0x3, 0x2, 0x2, 0x2, 0x3a7, 0x3aa, 
    0x3, 0x2, 0x2, 0x2, 0x3a8, 0x3a6, 0x3, 0x2, 0x2, 0x2, 0x3a8, 0x3a9, 
    0x3, 0x2, 0x2, 0x2, 0x3a9, 0x3ab, 0x3, 0x2, 0x2, 0x2, 0x3aa, 0x3a8, 
    0x3, 0x2, 0x2, 0x2, 0x3ab, 0x3b9, 0x7, 0x18, 0x2, 0x2, 0x3ac, 0x3b5, 
    0x7, 0x22, 0x2, 0x2, 0x3ad, 0x3b2, 0x5, 0x70, 0x39, 0x2, 0x3ae, 0x3af, 
    0x7, 0x11, 0x2, 0x2, 0x3af, 0x3b1, 0x5, 0x70, 0x39, 0x2, 0x3b0, 0x3ae, 
    0x3, 0x2, 0x2, 0x2, 0x3b1, 0x3b4, 0x3, 0x2, 0x2, 0x2, 0x3b2, 0x3b0, 
    0x3, 0x2, 0x2, 0x2, 0x3b2, 0x3b3, 0x3, 0x2, 0x2, 0x2, 0x3b3, 0x3b6, 
    0x3, 0x2, 0x2, 0x2, 0x3b4, 0x3b2, 0x3, 0x2, 0x2, 0x2, 0x3b5, 0x3ad, 
    0x3, 0x2, 0x2, 0x2, 0x3b5, 0x3b6, 0x3, 0x2, 0x2, 0x2, 0x3b6, 0x3b7, 
    0x3, 0x2, 0x2, 0x2, 0x3b7, 0x3b9, 0x7, 0x23, 0x2, 0x2, 0x3b8, 0x39e, 
    0x3, 0x2, 0x2, 0x2, 0x3b8, 0x3ac, 0x3, 0x2, 0x2, 0x2, 0x3b9, 0xa3, 0x3, 
    0x2, 0x2, 0x2, 0x3ba, 0x3bb, 0x5, 0x6e, 0x38, 0x2, 0x3bb, 0xa5, 0x3, 
    0x2, 0x2, 0x2, 0x3bc, 0x3be, 0x9, 0x11, 0x2, 0x2, 0x3bd, 0x3bf, 0x7, 
    0x66, 0x2, 0x2, 0x3be, 0x3bd, 0x3, 0x2, 0x2, 0x2, 0x3be, 0x3bf, 0x3, 
    0x2, 0x2, 0x2, 0x3bf, 0xa7, 0x3, 0x2, 0x2, 0x2, 0x3c0, 0x3c1, 0x9, 0x12, 
    0x2, 0x2, 0x3c1, 0xa9, 0x3, 0x2, 0x2, 0x2, 0x6a, 0xad, 0xaf, 0xbb, 0xbf, 
    0xc4, 0xcb, 0xd1, 0xd7, 0xdb, 0xe7, 0xef, 0xf9, 0xfc, 0x102, 0x10e, 
    0x113, 0x11d, 0x123, 0x129, 0x132, 0x140, 0x143, 0x14f, 0x156, 0x159, 
    0x15d, 0x162, 0x166, 0x171, 0x173, 0x17a, 0x184, 0x18a, 0x195, 0x198, 
    0x19e, 0x1a1, 0x1a9, 0x1ac, 0x1b2, 0x1b5, 0x1bd, 0x1c0, 0x1c6, 0x1ca, 
    0x1d5, 0x1da, 0x1df, 0x1e7, 0x1f6, 0x1f8, 0x1fd, 0x207, 0x218, 0x224, 
    0x22e, 0x234, 0x238, 0x23b, 0x242, 0x256, 0x268, 0x26c, 0x271, 0x275, 
    0x279, 0x27e, 0x283, 0x287, 0x29f, 0x2da, 0x2dc, 0x2e6, 0x2ec, 0x2ee, 
    0x2f5, 0x2fd, 0x301, 0x309, 0x30d, 0x30f, 0x31a, 0x330, 0x334, 0x33a, 
    0x33e, 0x344, 0x348, 0x34e, 0x359, 0x360, 0x36e, 0x377, 0x37d, 0x381, 
    0x38b, 0x390, 0x3a0, 0x3a4, 0x3a8, 0x3b2, 0x3b5, 0x3b8, 0x3be, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

SolidityParser::Initializer SolidityParser::_init;
