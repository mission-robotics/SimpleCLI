#ifndef TemplateReqArg_h
#define TemplateReqArg_h

#include "Arg.h"

class TemplateReqArg: public Arg {
  public:
    TemplateReqArg(const char* _template) {
      if (_template) {
        int strLen = strlen(_template);
        TemplateReqArg::_template = new char[strLen + 1];
        strcpy(TemplateReqArg::_template, _template);
        TemplateReqArg::_template[strLen] = '\0';
      }
      reset();
    }

    TemplateReqArg(String _template) {
      int strLen = _template.length() + 1;
      TemplateReqArg::_template = new char[strLen];
      _template.toCharArray(TemplateReqArg::_template, strLen);

      reset();
    }

    ~TemplateReqArg() {
      if (_template) delete _template;
      if (value) delete value;
      if (next) delete next;
    }

    bool equals(const char* name) {
      return strlen(name) == 0;
    }

    bool equals(String name) {
      return name.length() == 0;
    }

    void setValue(String value) {
      if (value.length() > 0) {

        index = cli_helper::equals(value.c_str(), _template);
        if (index >= 0) {
          if (TemplateReqArg::value) delete TemplateReqArg::value;

          int strLen = value.length() + 1;
          TemplateReqArg::value = new char[strLen];
          value.toCharArray(TemplateReqArg::value, strLen);

          set = true;
        }
      }
    }

    void reset() {
      if (value){
        delete value;
        value = NULL;
      }
      index = -1;
      Arg::reset();
    }

    String getValue() {
      return value ? String(value) : String();
    }

    bool isRequired() {
      return true;
    }

    int getValueIndex(){
      return index;
    }

  private:
    char* value = NULL;
    char* _template = NULL;
    int index = -1;
};

#endif