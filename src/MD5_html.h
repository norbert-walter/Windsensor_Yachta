String MD5()
{
 // Debug info 
 DebugPrintln(3, "Send MD5.html");

 String content;

  content +=F( "function MD5(string) {");
  
  content +=F( "function RotateLeft(lValue, iShiftBits) {");
  content +=F( "return (lValue << iShiftBits) | (lValue >>> (32 - iShiftBits));");
  content +=F( "}");
  
  content +=F( "function AddUnsigned(lX, lY) {");
  content +=F( "var lX4, lY4, lX8, lY8, lResult;");
  content +=F( "lX8 = (lX & 0x80000000);");
  content +=F( "lY8 = (lY & 0x80000000);");
  content +=F( "lX4 = (lX & 0x40000000);");
  content +=F( "lY4 = (lY & 0x40000000);");
  content +=F( "lResult = (lX & 0x3FFFFFFF) + (lY & 0x3FFFFFFF);");
  content +=F( "if (lX4 & lY4) {");
  content +=F( "return (lResult ^ 0x80000000 ^ lX8 ^ lY8);");
  content +=F( "}");
  content +=F( "if (lX4 | lY4) {");
  content +=F( "if (lResult & 0x40000000) {");
  content +=F( "return (lResult ^ 0xC0000000 ^ lX8 ^ lY8);");
  content +=F( "} else {");
  content +=F( "return (lResult ^ 0x40000000 ^ lX8 ^ lY8);");
  content +=F( "}");
  content +=F( "} else {");
  content +=F( "return (lResult ^ lX8 ^ lY8);");
  content +=F( "}");
  content +=F( "}");
  
  content +=F( "function F(x, y, z) {");
  content +=F( "return (x & y) | ((~x) & z);");
  content +=F( "}");
  
  content +=F( "function G(x, y, z) {");
  content +=F( "return (x & z) | (y & (~z));");
  content +=F( "}");
  
  content +=F( "function H(x, y, z) {");
  content +=F( "return (x ^ y ^ z);");
  content +=F( "}");
  
  content +=F( "function I(x, y, z) {");
  content +=F( "return (y ^ (x | (~z)));");
  content +=F( "}");
  
  content +=F( "function FF(a, b, c, d, x, s, ac) {");
  content +=F( "a = AddUnsigned(a, AddUnsigned(AddUnsigned(F(b, c, d), x), ac));");
  content +=F( "return AddUnsigned(RotateLeft(a, s), b);");
  content +=F( "};");
  
  content +=F( "function GG(a, b, c, d, x, s, ac) {");
  content +=F( "a = AddUnsigned(a, AddUnsigned(AddUnsigned(G(b, c, d), x), ac));");
  content +=F( "return AddUnsigned(RotateLeft(a, s), b);");
  content +=F( "};");
  
  content +=F( "function HH(a, b, c, d, x, s, ac) {");
  content +=F( "a = AddUnsigned(a, AddUnsigned(AddUnsigned(H(b, c, d), x), ac));");
  content +=F( "return AddUnsigned(RotateLeft(a, s), b);");
  content +=F( "};");
  
  content +=F( "function II(a, b, c, d, x, s, ac) {");
  content +=F( "a = AddUnsigned(a, AddUnsigned(AddUnsigned(I(b, c, d), x), ac));");
  content +=F( "return AddUnsigned(RotateLeft(a, s), b);");
  content +=F( "};");
  
  content +=F( "function ConvertToWordArray(string) {");
  content +=F( "var lWordCount;");
  content +=F( "var lMessageLength = string.length;");
  content +=F( "var lNumberOfWords_temp1 = lMessageLength + 8;");
  content +=F( "var lNumberOfWords_temp2 = (lNumberOfWords_temp1 - (lNumberOfWords_temp1 % 64)) / 64;");
  content +=F( "var lNumberOfWords = (lNumberOfWords_temp2 + 1) * 16;");
  content +=F( "var lWordArray = Array(lNumberOfWords - 1);");
  content +=F( "var lBytePosition = 0;");
  content +=F( "var lByteCount = 0;");
  content +=F( "while (lByteCount < lMessageLength) {");
  content +=F( "lWordCount = (lByteCount - (lByteCount % 4)) / 4;");
  content +=F( "lBytePosition = (lByteCount % 4) * 8;");
  content +=F( "lWordArray[lWordCount] = (lWordArray[lWordCount] | (string.charCodeAt(lByteCount) << lBytePosition));");
  content +=F( "lByteCount++;");
  content +=F( "}");
  content +=F( "lWordCount = (lByteCount - (lByteCount % 4)) / 4;");
  content +=F( "lBytePosition = (lByteCount % 4) * 8;");
  content +=F( "lWordArray[lWordCount] = lWordArray[lWordCount] | (0x80 << lBytePosition);");
  content +=F( "lWordArray[lNumberOfWords - 2] = lMessageLength << 3;");
  content +=F( "lWordArray[lNumberOfWords - 1] = lMessageLength >>> 29;");
  content +=F( "return lWordArray;");
  content +=F( "};");
  
  content +=F( "function WordToHex(lValue) {");
  content +=F( "var WordToHexValue = \"\",");
  content +=F( "WordToHexValue_temp = \"\",");
  content +=F( "lByte, lCount;");
  content +=F( "for (lCount = 0; lCount <= 3; lCount++) {");
  content +=F( "lByte = (lValue >>> (lCount * 8)) & 255;");
  content +=F( "WordToHexValue_temp = \"0\" + lByte.toString(16);");
  content +=F( "WordToHexValue = WordToHexValue + WordToHexValue_temp.substr(WordToHexValue_temp.length - 2, 2);");
  content +=F( "}");
  content +=F( "return WordToHexValue;");
  content +=F( "};");
  
  content +=F( "function Utf8Encode(string) {");
  content +=F( "string = string.replace(/\\r\\n/g, \"\\n\");");
  content +=F( "var utftext = \"\";");
  content +=F( "for (var n = 0; n < string.length; n++) {");
  content +=F( "var c = string.charCodeAt(n);");
  content +=F( "if (c < 128) {");
  content +=F( "utftext += String.fromCharCode(c);");
  content +=F( "} else if ((c > 127) && (c < 2048)) {");
  content +=F( "utftext += String.fromCharCode((c >> 6) | 192);");
  content +=F( "utftext += String.fromCharCode((c & 63) | 128);");
  content +=F( "} else {");
  content +=F( "utftext += String.fromCharCode((c >> 12) | 224);");
  content +=F( "utftext += String.fromCharCode(((c >> 6) & 63) | 128);");
  content +=F( "utftext += String.fromCharCode((c & 63) | 128);");
  content +=F( "}");
  content +=F( "}");
  content +=F( "return utftext;");
  content +=F( "};");
  
  content +=F( "var x = Array();");
  content +=F( "var k, AA, BB, CC, DD, a, b, c, d;");
  content +=F( "var S11 = 7, S12 = 12, S13 = 17, S14 = 22;");
  content +=F( "var S21 = 5, S22 = 9, S23 = 14, S24 = 20;");
  content +=F( "var S31 = 4, S32 = 11, S33 = 16, S34 = 23;");
  content +=F( "var S41 = 6, S42 = 10, S43 = 15, S44 = 21;");
  
  content +=F( "string = Utf8Encode(string);");
  
  content +=F( "x = ConvertToWordArray(string);");
  
  content +=F( "a = 0x67452301;");
  content +=F( "b = 0xEFCDAB89;");
  content +=F( "c = 0x98BADCFE;");
  content +=F( "d = 0x10325476;");
  
  content +=F( "for (k = 0; k < x.length; k += 16) {");
  content +=F( "AA = a;");
  content +=F( "BB = b;");
  content +=F( "CC = c;");
  content +=F( "DD = d;");
  content +=F( "a = FF(a, b, c, d, x[k + 0], S11, 0xD76AA478);");
  content +=F( "d = FF(d, a, b, c, x[k + 1], S12, 0xE8C7B756);");
  content +=F( "c = FF(c, d, a, b, x[k + 2], S13, 0x242070DB);");
  content +=F( "b = FF(b, c, d, a, x[k + 3], S14, 0xC1BDCEEE);");
  content +=F( "a = FF(a, b, c, d, x[k + 4], S11, 0xF57C0FAF);");
  content +=F( "d = FF(d, a, b, c, x[k + 5], S12, 0x4787C62A);");
  content +=F( "c = FF(c, d, a, b, x[k + 6], S13, 0xA8304613);");
  content +=F( "b = FF(b, c, d, a, x[k + 7], S14, 0xFD469501);");
  content +=F( "a = FF(a, b, c, d, x[k + 8], S11, 0x698098D8);");
  content +=F( "d = FF(d, a, b, c, x[k + 9], S12, 0x8B44F7AF);");
  content +=F( "c = FF(c, d, a, b, x[k + 10], S13, 0xFFFF5BB1);");
  content +=F( "b = FF(b, c, d, a, x[k + 11], S14, 0x895CD7BE);");
  content +=F( "a = FF(a, b, c, d, x[k + 12], S11, 0x6B901122);");
  content +=F( "d = FF(d, a, b, c, x[k + 13], S12, 0xFD987193);");
  content +=F( "c = FF(c, d, a, b, x[k + 14], S13, 0xA679438E);");
  content +=F( "b = FF(b, c, d, a, x[k + 15], S14, 0x49B40821);");
  content +=F( "a = GG(a, b, c, d, x[k + 1], S21, 0xF61E2562);");
  content +=F( "d = GG(d, a, b, c, x[k + 6], S22, 0xC040B340);");
  content +=F( "c = GG(c, d, a, b, x[k + 11], S23, 0x265E5A51);");
  content +=F( "b = GG(b, c, d, a, x[k + 0], S24, 0xE9B6C7AA);");
  content +=F( "a = GG(a, b, c, d, x[k + 5], S21, 0xD62F105D);");
  content +=F( "d = GG(d, a, b, c, x[k + 10], S22, 0x2441453);");
  content +=F( "c = GG(c, d, a, b, x[k + 15], S23, 0xD8A1E681);");
  content +=F( "b = GG(b, c, d, a, x[k + 4], S24, 0xE7D3FBC8);");
  content +=F( "a = GG(a, b, c, d, x[k + 9], S21, 0x21E1CDE6);");
  content +=F( "d = GG(d, a, b, c, x[k + 14], S22, 0xC33707D6);");
  content +=F( "c = GG(c, d, a, b, x[k + 3], S23, 0xF4D50D87);");
  content +=F( "b = GG(b, c, d, a, x[k + 8], S24, 0x455A14ED);");
  content +=F( "a = GG(a, b, c, d, x[k + 13], S21, 0xA9E3E905);");
  content +=F( "d = GG(d, a, b, c, x[k + 2], S22, 0xFCEFA3F8);");
  content +=F( "c = GG(c, d, a, b, x[k + 7], S23, 0x676F02D9);");
  content +=F( "b = GG(b, c, d, a, x[k + 12], S24, 0x8D2A4C8A);");
  content +=F( "a = HH(a, b, c, d, x[k + 5], S31, 0xFFFA3942);");
  content +=F( "d = HH(d, a, b, c, x[k + 8], S32, 0x8771F681);");
  content +=F( "c = HH(c, d, a, b, x[k + 11], S33, 0x6D9D6122);");
  content +=F( "b = HH(b, c, d, a, x[k + 14], S34, 0xFDE5380C);");
  content +=F( "a = HH(a, b, c, d, x[k + 1], S31, 0xA4BEEA44);");
  content +=F( "d = HH(d, a, b, c, x[k + 4], S32, 0x4BDECFA9);");
  content +=F( "c = HH(c, d, a, b, x[k + 7], S33, 0xF6BB4B60);");
  content +=F( "b = HH(b, c, d, a, x[k + 10], S34, 0xBEBFBC70);");
  content +=F( "a = HH(a, b, c, d, x[k + 13], S31, 0x289B7EC6);");
  content +=F( "d = HH(d, a, b, c, x[k + 0], S32, 0xEAA127FA);");
  content +=F( "c = HH(c, d, a, b, x[k + 3], S33, 0xD4EF3085);");
  content +=F( "b = HH(b, c, d, a, x[k + 6], S34, 0x4881D05);");
  content +=F( "a = HH(a, b, c, d, x[k + 9], S31, 0xD9D4D039);");
  content +=F( "d = HH(d, a, b, c, x[k + 12], S32, 0xE6DB99E5);");
  content +=F( "c = HH(c, d, a, b, x[k + 15], S33, 0x1FA27CF8);");
  content +=F( "b = HH(b, c, d, a, x[k + 2], S34, 0xC4AC5665);");
  content +=F( "a = II(a, b, c, d, x[k + 0], S41, 0xF4292244);");
  content +=F( "d = II(d, a, b, c, x[k + 7], S42, 0x432AFF97);");
  content +=F( "c = II(c, d, a, b, x[k + 14], S43, 0xAB9423A7);");
  content +=F( "b = II(b, c, d, a, x[k + 5], S44, 0xFC93A039);");
  content +=F( "a = II(a, b, c, d, x[k + 12], S41, 0x655B59C3);");
  content +=F( "d = II(d, a, b, c, x[k + 3], S42, 0x8F0CCC92);");
  content +=F( "c = II(c, d, a, b, x[k + 10], S43, 0xFFEFF47D);");
  content +=F( "b = II(b, c, d, a, x[k + 1], S44, 0x85845DD1);");
  content +=F( "a = II(a, b, c, d, x[k + 8], S41, 0x6FA87E4F);");
  content +=F( "d = II(d, a, b, c, x[k + 15], S42, 0xFE2CE6E0);");
  content +=F( "c = II(c, d, a, b, x[k + 6], S43, 0xA3014314);");
  content +=F( "b = II(b, c, d, a, x[k + 13], S44, 0x4E0811A1);");
  content +=F( "a = II(a, b, c, d, x[k + 4], S41, 0xF7537E82);");
  content +=F( "d = II(d, a, b, c, x[k + 11], S42, 0xBD3AF235);");
  content +=F( "c = II(c, d, a, b, x[k + 2], S43, 0x2AD7D2BB);");
  content +=F( "b = II(b, c, d, a, x[k + 9], S44, 0xEB86D391);");
  content +=F( "a = AddUnsigned(a, AA);");
  content +=F( "b = AddUnsigned(b, BB);");
  content +=F( "c = AddUnsigned(c, CC);");
  content +=F( "d = AddUnsigned(d, DD);");
  content +=F( "}");
  
  content +=F( "var temp = WordToHex(a) + WordToHex(b) + WordToHex(c) + WordToHex(d);");
  
  content +=F( "return temp.toLowerCase();");
  content +=F( "}");
  
  content +=F( "function crypt(text) {");
//  content +=F( "var transactionID = 12345678;");
  content +=F( "var transactionID = ");
  content += String(transactionID);
  content +=F( ";");
  content +=F( "var rawdata = text.toString().concat(transactionID.toString());");
  content +=F( "return MD5(rawdata);");
  content +=F( "}");
  
  content +=F( "function send(hash) {");
  content +=F( "document.querySelector(\"#password\").value = hash;");
  content +=F( "document.getElementById(\"pwdForm\").submit();");
  content +=F( "document.querySelector(\"#password\").value = \"\";");
  content +=F( "}");
  
  content +=F( "function proc() {");
  content +=F( "var reguexp = /[^A-z0-9]/;");
  content +=F( "var valuestring = document.querySelector(\"#password\").value;");
  content +=F( "if (reguexp.exec(valuestring) || valuestring.length < 8 || valuestring.length > 20) {");
  content +=F( "alert('Error!\\nUse only a-z, A-Z, 0-9\\nPassword Length 8-20');");
  content +=F( "return;");
  content +=F( "}");
  content +=F( "var input = document.querySelector(\"#password\").value;");
  content +=F( "var password = input.toString();");
  content +=F( "var hash = crypt(password);");
  content +=F( "send(hash);");
  content +=F( "}");

 return content;
}
