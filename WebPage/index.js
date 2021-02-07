function onOkClicked() {
    var txtUser = document.getElementById("txtUser");
    var txtPassword = document.getElementById("txtPassword");
    var result = document.getElementById("result");
    result.innerHTML = "Welcome: " + txtUser.value + " with password: " + txtPassword.value;
}