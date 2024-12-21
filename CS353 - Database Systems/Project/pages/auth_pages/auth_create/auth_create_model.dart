import '/auth/firebase_auth/auth_util.dart';
import '/components/main_components/main_logo_small/main_logo_small_widget.dart';
import '/flutter_flow/flutter_flow_animations.dart';
import '/flutter_flow/flutter_flow_theme.dart';
import '/flutter_flow/flutter_flow_util.dart';
import '/flutter_flow/flutter_flow_widgets.dart';
import 'auth_create_widget.dart' show AuthCreateWidget;
import 'package:auto_size_text/auto_size_text.dart';
import 'package:flutter/material.dart';
import 'package:flutter/scheduler.dart';
import 'package:flutter/services.dart';
import 'package:flutter_animate/flutter_animate.dart';
import 'package:font_awesome_flutter/font_awesome_flutter.dart';
import 'package:google_fonts/google_fonts.dart';
import 'package:provider/provider.dart';

class AuthCreateModel extends FlutterFlowModel<AuthCreateWidget> {
  ///  State fields for stateful widgets in this page.

  final unfocusNode = FocusNode();
  // Model for main_Logo_Small component.
  late MainLogoSmallModel mainLogoSmallModel;
  // State field(s) for emailAddress widget.
  FocusNode? emailAddressFocusNode;
  TextEditingController? emailAddressController;
  String? Function(BuildContext, String?)? emailAddressControllerValidator;
  // State field(s) for password widget.
  FocusNode? passwordFocusNode;
  TextEditingController? passwordController;
  late bool passwordVisibility;
  String? Function(BuildContext, String?)? passwordControllerValidator;
  // State field(s) for passwordConfirm widget.
  FocusNode? passwordConfirmFocusNode1;
  TextEditingController? passwordConfirmController1;
  late bool passwordConfirmVisibility1;
  String? Function(BuildContext, String?)? passwordConfirmController1Validator;
  // State field(s) for passwordConfirm widget.
  FocusNode? passwordConfirmFocusNode2;
  TextEditingController? passwordConfirmController2;
  late bool passwordConfirmVisibility2;
  String? Function(BuildContext, String?)? passwordConfirmController2Validator;
  // State field(s) for passwordConfirm widget.
  FocusNode? passwordConfirmFocusNode3;
  TextEditingController? passwordConfirmController3;
  late bool passwordConfirmVisibility3;
  String? Function(BuildContext, String?)? passwordConfirmController3Validator;

  /// Initialization and disposal methods.

  void initState(BuildContext context) {
    mainLogoSmallModel = createModel(context, () => MainLogoSmallModel());
    passwordVisibility = false;
    passwordConfirmVisibility1 = false;
    passwordConfirmVisibility2 = false;
    passwordConfirmVisibility3 = false;
  }

  void dispose() {
    unfocusNode.dispose();
    mainLogoSmallModel.dispose();
    emailAddressFocusNode?.dispose();
    emailAddressController?.dispose();

    passwordFocusNode?.dispose();
    passwordController?.dispose();

    passwordConfirmFocusNode1?.dispose();
    passwordConfirmController1?.dispose();

    passwordConfirmFocusNode2?.dispose();
    passwordConfirmController2?.dispose();

    passwordConfirmFocusNode3?.dispose();
    passwordConfirmController3?.dispose();
  }

  /// Action blocks are added here.

  /// Additional helper methods are added here.
}
